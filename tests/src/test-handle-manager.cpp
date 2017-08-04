/***********************************/
/* Test: handle-manager         */
/* By: Karl Hansson 2017           */
/***********************************/

#include <Catch/catch.hpp>

#include <kfx/Assert.h>
#include <kfx/HandleManager.h>

SCENARIO("Adding and removing handles to a handle manager", "[handle]") {
  GIVEN("An empty handle manager") {
    kfx::HandleManager handle_manager;

    WHEN("adding a new resource as an entry") {
      THEN("a valid handle to the same resource is returned") {
        int resource = 5;

        kfx::Handle handle = handle_manager.addEntry(&resource);
        REQUIRE(handle != kfx::Handle::NULL_HANDLE);

        int* pointer_to_resource =
            static_cast<int*>(handle_manager.getEntry(handle));

        REQUIRE(resource == *pointer_to_resource);
      }
    }

    WHEN("attempting to remove a non-existant entry") {
      THEN("the function throws") {
        kfx::Handle fake_handle = kfx::Handle(1, 0);
        fake_handle.m_is_initialized = true;

        REQUIRE_THROWS_AS(handle_manager.removeEntry(fake_handle),
                          kfx::KfxContractFailure);
      }
    }

    WHEN("attempting to update a non-existant entry") {
      THEN("the function throws") {
        kfx::Handle fake_handle = kfx::Handle(1, 0);
        fake_handle.m_is_initialized = true;

        REQUIRE_THROWS_AS(handle_manager.updateEntry(fake_handle, nullptr),
                          kfx::KfxContractFailure);
      }
    }

    WHEN("attempting to get a non-existant entry") {
      THEN("the function throws") {
        kfx::Handle fake_handle = kfx::Handle(1, 0);
        fake_handle.m_is_initialized = true;

        REQUIRE_THROWS_AS(handle_manager.getEntry(fake_handle),
                          kfx::KfxContractFailure);
      }
    }

    WHEN("attempting to remove with an uninitialized handle") {
      THEN("the function throws") {
        kfx::Handle fake_handle = kfx::Handle(1, 0);

        REQUIRE_THROWS_AS(handle_manager.removeEntry(fake_handle),
                          kfx::KfxContractFailure);
      }
    }

    WHEN("attempting to update with an uninitialized handle") {
      THEN("the function throws") {
        kfx::Handle fake_handle = kfx::Handle(1, 0);

        REQUIRE_THROWS_AS(handle_manager.updateEntry(fake_handle, nullptr),
                          kfx::KfxContractFailure);
      }
    }
  }

  // ====================
  //
  // ====================

  GIVEN("A non-empty handle manager") {
    kfx::HandleManager handle_manager;
    int a = 1, b = 2, c = 3;
    kfx::Handle handle_1 = handle_manager.addEntry(&a);
    kfx::Handle handle_2 = handle_manager.addEntry(&b);
    kfx::Handle handle_3 = handle_manager.addEntry(&c);
    REQUIRE(handle_1 != kfx::Handle::NULL_HANDLE);
    REQUIRE(handle_2 != kfx::Handle::NULL_HANDLE);
    REQUIRE(handle_3 != kfx::Handle::NULL_HANDLE);

    WHEN("adding the resource as an entry") {
      THEN("a valid handle to the same resource is returned") {
        int resource = 5;

        kfx::Handle handle = handle_manager.addEntry(&resource);
        REQUIRE(handle != kfx::Handle::NULL_HANDLE);

        int* pointer_to_resource =
            static_cast<int*>(handle_manager.getEntry(handle));

        REQUIRE(resource == *pointer_to_resource);
      }
    }

    WHEN("Removing an entry with a valid handle") {
      THEN("the entry is removed") {
        REQUIRE_NOTHROW(handle_manager.getEntry(handle_1));
        REQUIRE(static_cast<int*>(handle_manager.getEntry(handle_1)) == &a);
        REQUIRE_NOTHROW(handle_manager.removeEntry(handle_1));
        REQUIRE_THROWS_AS(handle_manager.getEntry(handle_1),
                          kfx::KfxContractFailure);
      }
    }

    WHEN("Updating an entry with a valid handle") {
      THEN("the entry is updated") {
        REQUIRE(static_cast<int*>(handle_manager.getEntry(handle_2)) == &b);
        REQUIRE_NOTHROW(handle_manager.updateEntry(handle_2, nullptr));
        REQUIRE(static_cast<int*>(handle_manager.getEntry(handle_2)) ==
                nullptr);
      }
    }

    WHEN("Getting an entry with a valid handle") {
      THEN("the entry is returned") {
        REQUIRE_NOTHROW(handle_manager.getEntry(handle_3));
        REQUIRE(static_cast<int*>(handle_manager.getEntry(handle_3)) == &c);
      }
    }

    WHEN("attempting to remove a non-existant entry") {
      THEN("the function throws") {
        kfx::Handle fake_handle = kfx::Handle(1, 4);
        fake_handle.m_is_initialized = true;

        REQUIRE_THROWS_AS(handle_manager.removeEntry(fake_handle),
                          kfx::KfxContractFailure);
      }
    }

    WHEN("attempting to update a non-existant entry") {
      THEN("the function throws") {
        kfx::Handle fake_handle = kfx::Handle(1, 4);
        fake_handle.m_is_initialized = true;

        REQUIRE_THROWS_AS(handle_manager.updateEntry(fake_handle, nullptr),
                          kfx::KfxContractFailure);
      }
    }

    WHEN("attempting to get a non-existant entry") {
      THEN("the function throws") {
        kfx::Handle fake_handle = kfx::Handle(1, 4);
        fake_handle.m_is_initialized = true;

        REQUIRE_THROWS_AS(handle_manager.getEntry(fake_handle),
                          kfx::KfxContractFailure);
      }
    }

    WHEN("attempting to remove with an uninitialized handle") {
      THEN("the function throws") {
        kfx::Handle fake_handle = kfx::Handle(1, 4);

        REQUIRE_THROWS_AS(handle_manager.removeEntry(fake_handle),
                          kfx::KfxContractFailure);
      }
    }

    WHEN("attempting to update with an uninitialized handle") {
      THEN("the function throws") {
        kfx::Handle fake_handle = kfx::Handle(1, 4);

        REQUIRE_THROWS_AS(handle_manager.updateEntry(fake_handle, nullptr),
                          kfx::KfxContractFailure);
      }
    }

    WHEN("attempting to get with an uninitialized handle") {
      THEN("the function throws") {
        kfx::Handle fake_handle = kfx::Handle(1, 4);

        REQUIRE_THROWS_AS(handle_manager.getEntry(fake_handle),
                          kfx::KfxContractFailure);
      }
    }

    WHEN("Removing all current handles") {
      REQUIRE(handle_1.m_index == 0);
      REQUIRE(handle_2.m_index == 1);
      REQUIRE(handle_3.m_index == 2);
      handle_manager.removeEntry(handle_1);
      handle_manager.removeEntry(handle_2);
      handle_manager.removeEntry(handle_3);

      AND_WHEN("Adding new handles (replace the old)") {
        kfx::Handle handle_1b = handle_manager.addEntry(nullptr);
        kfx::Handle handle_2b = handle_manager.addEntry(nullptr);
        kfx::Handle handle_3b = handle_manager.addEntry(nullptr);
        REQUIRE(handle_1b != kfx::Handle::NULL_HANDLE);
        REQUIRE(handle_2b != kfx::Handle::NULL_HANDLE);
        REQUIRE(handle_3b != kfx::Handle::NULL_HANDLE);
        REQUIRE(handle_1b.m_index == 0);
        REQUIRE(handle_2b.m_index == 1);
        REQUIRE(handle_3b.m_index == 2);

        THEN("The old handles have become invalid") {
          REQUIRE_THROWS_AS(handle_manager.getEntry(handle_1),
                            kfx::KfxContractFailure);
          REQUIRE_THROWS_AS(handle_manager.getEntry(handle_2),
                            kfx::KfxContractFailure);
          REQUIRE_THROWS_AS(handle_manager.getEntry(handle_3),
                            kfx::KfxContractFailure);
          REQUIRE_NOTHROW(handle_manager.getEntry(handle_1b));
          REQUIRE_NOTHROW(handle_manager.getEntry(handle_2b));
          REQUIRE_NOTHROW(handle_manager.getEntry(handle_3b));
        }
      }
    }
  }

  // ====================
  //
  // ====================

  GIVEN("A full handle manager") {
    int a = 5;
    kfx::HandleManager handle_manager;
    for (int i = 0; i < kfx::Handle::MAX_HANDLES; i++) {
      REQUIRE(handle_manager.addEntry(&a) != kfx::Handle::NULL_HANDLE);
    }

    REQUIRE(handle_manager.isFull() == true);

    WHEN("adding an entry") {
      REQUIRE(handle_manager.isFull() == true);

      int resource = 5;
      kfx::Handle handle = handle_manager.addEntry(&resource);

      THEN("a null handle is returned") {
        REQUIRE(handle == kfx::Handle::NULL_HANDLE);
      }
    }

    WHEN("removing the first entry") {
      REQUIRE(handle_manager.isFull() == true);

      kfx::Handle handle = kfx::Handle(1, 0);
      handle.m_is_initialized = true;
      REQUIRE(static_cast<int*>(handle_manager.getEntry(handle)) == &a);
      REQUIRE_NOTHROW(handle_manager.removeEntry(handle));

      THEN("the entry is removed") {
        REQUIRE_THROWS_AS(handle_manager.getEntry(handle),
                          kfx::KfxContractFailure);
      }
    }

    WHEN("removing the middle entry") {
      REQUIRE(handle_manager.isFull() == true);

      kfx::Handle handle = kfx::Handle(1, kfx::Handle::MAX_HANDLES / 2);
      handle.m_is_initialized = true;
      REQUIRE(static_cast<int*>(handle_manager.getEntry(handle)) == &a);
      REQUIRE_NOTHROW(handle_manager.removeEntry(handle));

      THEN("the entry is removed") {
        REQUIRE_THROWS_AS(handle_manager.getEntry(handle),
                          kfx::KfxContractFailure);
      }
    }

    WHEN("removing the last entry") {
      REQUIRE(handle_manager.isFull() == true);

      kfx::Handle handle = kfx::Handle(1, kfx::Handle::MAX_HANDLES - 1);
      handle.m_is_initialized = true;
      REQUIRE(static_cast<int*>(handle_manager.getEntry(handle)) == &a);
      REQUIRE_NOTHROW(handle_manager.removeEntry(handle));

      THEN("the entry is removed") {
        REQUIRE_THROWS_AS(handle_manager.getEntry(handle),
                          kfx::KfxContractFailure);
      }
    }

    WHEN("updating the first entry") {
      REQUIRE(handle_manager.isFull() == true);

      kfx::Handle handle = kfx::Handle(1, 0);
      handle.m_is_initialized = true;
      REQUIRE(static_cast<int*>(handle_manager.getEntry(handle)) == &a);
      REQUIRE_NOTHROW(handle_manager.updateEntry(handle, nullptr));

      THEN("the entry is updated") {
        REQUIRE(static_cast<int*>(handle_manager.getEntry(handle)) == nullptr);
      }
    }

    WHEN("updating the middle entry") {
      REQUIRE(handle_manager.isFull() == true);

      kfx::Handle handle = kfx::Handle(1, kfx::Handle::MAX_HANDLES / 2);
      handle.m_is_initialized = true;
      REQUIRE(static_cast<int*>(handle_manager.getEntry(handle)) == &a);
      REQUIRE_NOTHROW(handle_manager.updateEntry(handle, nullptr));

      THEN("the entry is updated") {
        REQUIRE(static_cast<int*>(handle_manager.getEntry(handle)) == nullptr);
      }
    }

    WHEN("updating the last entry") {
      REQUIRE(handle_manager.isFull() == true);

      kfx::Handle handle = kfx::Handle(1, kfx::Handle::MAX_HANDLES - 1);
      handle.m_is_initialized = true;
      REQUIRE(static_cast<int*>(handle_manager.getEntry(handle)) == &a);
      REQUIRE_NOTHROW(handle_manager.updateEntry(handle, nullptr));

      THEN("the entry is updated") {
        REQUIRE(static_cast<int*>(handle_manager.getEntry(handle)) == nullptr);
      }
    }

    WHEN("getting the first entry") {
      REQUIRE(handle_manager.isFull() == true);

      kfx::Handle handle = kfx::Handle(1, 0);
      handle.m_is_initialized = true;
      int* pointer_to_a = static_cast<int*>(handle_manager.getEntry(handle));

      THEN("the entry is returned") { REQUIRE(*pointer_to_a == a); }
    }

    WHEN("getting the middle entry") {
      REQUIRE(handle_manager.isFull() == true);

      kfx::Handle handle = kfx::Handle(1, kfx::Handle::MAX_HANDLES / 2);
      handle.m_is_initialized = true;
      int* pointer_to_a = static_cast<int*>(handle_manager.getEntry(handle));

      THEN("the entry is returned") { REQUIRE(*pointer_to_a == a); }
    }

    WHEN("getting the last entry") {
      REQUIRE(handle_manager.isFull() == true);

      kfx::Handle handle = kfx::Handle(1, kfx::Handle::MAX_HANDLES - 1);
      handle.m_is_initialized = true;
      int* pointer_to_a = static_cast<int*>(handle_manager.getEntry(handle));

      THEN("the entry is returned") { REQUIRE(*pointer_to_a == a); }
    }
  }
}
