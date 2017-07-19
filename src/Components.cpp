#include "kfx/Components.h"

namespace kfx {
	TransformComponent::TransformComponent() 
	: m_position(0.f)
	, m_rotation(0.f)
	, m_scale(1.f)
	, m_model(1.f)
	, m_should_update(false) {

	}

	void TransformComponent::lookAt(glm::vec3 target, glm::vec3 up) {
		glm::mat4 look_at_matrix = glm::transpose(glm::lookAt(m_position, target, up));
		
		const float r31 = look_at_matrix[3][1];
		const float r32 = look_at_matrix[3][2];
		const float r33 = look_at_matrix[3][3];
		const float r21 = look_at_matrix[2][1];
		const float r11 = look_at_matrix[1][1];

		m_rotation.x = atan2(r32, r33);
		m_rotation.y = atan2(-r31, sqrtf(r32*r32 + r33*r33));
		m_rotation.z = atan2(r21, r11);

		m_should_update = true;
	}

	glm::mat4 TransformComponent::getModel() {
		if (m_should_update) {
			glm::mat4 translation_matrix = glm::translate(m_position);
			
			glm::mat4 rot_x_matrix = glm::rotate(m_rotation.x, glm::vec3(1, 0, 0));
			glm::mat4 rot_y_matrix = glm::rotate(m_rotation.y, glm::vec3(0, 1, 0));
			glm::mat4 rot_z_matrix = glm::rotate(m_rotation.z, glm::vec3(0, 0, 1));

			glm::mat4 rotation_matrix = rot_z_matrix * rot_y_matrix * rot_x_matrix;

			glm::mat4 scale_matrix = glm::scale(m_scale);

			m_model = translation_matrix * rotation_matrix * scale_matrix;

			m_should_update = false;
		}

		return m_model;
	}

}