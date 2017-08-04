# KFX

## PLEASE NOTE

This project, while public, was mostly intended for private use between
me and friends who wanted to try it out. If you want something similar that is stable and up to date, I suggest you look elsewhere. That said, feel free to clone it if you really want.
I make no guarantees to safety, correctness and so forth. I simply made this
to improve myself and learn basic project management tools such as CMake,
Unit Testing, Doxygen and Continous integration, along with making something
that works.

## What is KFX?

KFX is my personal attempt at making a somewhat reusable library of
typical game-engine features. At first I simply wanted it to be an
executable graphics demo, but over time decided I wanted to make it
more general.


## How to (hopefully) build

Navigate to the project's root directory,
then, for an out of source build (recommended),
navigate into the build directory.
From there, you can execute cmake and build the project with
```
cmake ..
cmake --build . --target all --config Release
# Note that you can change the configuration to Debug if you want
```
The project should now have been built, and you should find a
few library files in the lib folder, and some executables
(tests and examples) in the bin folder.
