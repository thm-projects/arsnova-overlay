# General Information

## Description
ARSnova Overlay is a small widget to display information taken from arsnova.eu or other ARSnova servers.

### Usage
You should be able to run ARSnova Overlay from desktop. It starts with a simple
graphical user interface which allows to enter a ARSnova session key.
After entering a valid key, the application will show some information about
the session this application is connected to.

For more information see the users manual.

### More information

To get information about how to build ARSnova Overlay, take a look at the build instructions.

ARSnova Overlay uses unit testing. Make shoure you have read the testing instruction on how to use unit testing.

## Build instructions
This application is based on the Qt Framework. If you could not find a package
for your platform you must have installed the following packages:
* Qt Framework 5.2+
* CMake
* A C++ compiler (GCC and Clang/LLVM will work fine)

If you use a sourcecode package, ensure you have libqrcode sourcecode included in 'extern' folder.

If cloning from Git, additionaly type:
    git submodule update --init
to fetch libqrencode sourcecode.

To compile, simply type:
    cmake . && make
in the projects sourcecode folder.

To create an installation package, type:
    cpack
and the installation package will be created in base folder.

### Information for use with OS X
Systems with OS X require an prepared environment to point to the clang_64 folder:
    export QTDIR=/Application/Qt5.x.y/5.x/clang_64

In addition to that, it might be necessary to call `cpack` with full path within `CMake.app`.

## Testing instructions
ARSnova Overlay uses unit tests to ensure a higher quality of the resulting software.
To ensure not to break any existing unit tests (which at most will result in
software bugs) your are REQUIRED to write your own tests for new code you provide.

To write tests, take a look at the existing tests to see how they are used.

To tun the tests you must enable the use of unit tests by typing:
    cmake -DTESTS=ON && make
This will compile the test application.

To run all tests should type:
    ctest

This will run all existing tests.

## Code coverage
To ensure that most parts of the sourcecode are tested, we provide a build target,
providing easy code coverage generation.

You should type:
    cmake -DCOVERAGE=ON

To enable code coverage for this project. To create a coverage report, type:
    ctest && make coverage
This will create a coverage report in subfolder 'coverage'.
