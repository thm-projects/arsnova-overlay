/**
 *   Copyright (C) 2012  Paul-Christian Volkmer
 *   <paul-christian.volkmer@mni.thm.de>
 *
 *   This file is part of ARSnovaDesktop.
 *
 *   ARSnovaDesktop is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   ARSnovaDesktop is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with ARSnovaDesktop.  If not, see <http://www.gnu.org/licenses/>.
 */

/*************************************************************
 * 
 * This file holds documentation pages to be used with doxygen
 * 
 ***********************************************************/

/**
 * @mainpage General Information
 * 
 * @section description Description
 * ARSnovaDesktop is a small widget to display information taken from ars.thm.de
 * 
 * @section usage Usage
 * You should be able to run ARSnovaDesktop from desktop. It starts with a simple
 * graphical user interface which allows to enter a ARSnova session key.
 * 
 * After entering a valid key, the application will show some information about
 * the session this application is connected to.
 * 
 * For more information see the users manual.
 * 
 * @section moreinfo More information
 * 
 * To get information about how to build ARSnovaDesktop, take a look at the
 * @link build build instructions @endlink.
 * 
 * ARSnovaDesktop uses unit testing. Make shoure you have read the
 * @link testing testing instruction @endlink on how to use unit testing.
 * 
 * @page build Build instructions
 * This application is based on the Qt Framework. If you could not find a package
 * for your platform you must have installed the following packages:
 *   - Qt Framework 4.8+
 *   - CMake
 *   - A C++ compiler (GCC and Clang/LLVM will work fine)
 * 
 * If you use a sourcecode package, ensure you have libqrcode sourcecode included
 * in 'extern' folder.
 * If cloning from Git, additionaly type:
 * @code
 *   git submodule update --init
 * @endcode
 * to fetch libqrencode sourcecode.
 * 
 * To compile, simply type:
 * @code
 *   cmake . && make
 * @endcode
 * in the projects sourcecode folder. The binary will be available in 'bin' folder.
 * 
 * To create an installation package, type:
 * @code
 *   cpack
 * @endcode
 * and the installation package will be created in base folder.
 * 
 * @page testing Testing instructions
 * ARSnovaDesktop uses unit tests to ensure a higher quality of the resulting software.
 * To ensure not to break any existing unit tests (which at most will result in
 * software bugs) your are REQUIRED to write your own tests for new code you provide.
 *
 * To write tests, take a look at the existing tests to see how they are used.
 *
 * To tun the tests you must enable the use of unit tests by typing:
 * @code
 *   cmake -DTESTS=ON && make
 * @endcode
 * This will compile the test application.
 * 
 * To run all tests should type:
 * @code
 *   ctest
 * @endcode
 * This will run all existing tests.
 *
 * @section codecoverage Code coverage
 * To ensure that most parts of the sourcecode are tested, we provide a build
 * target, providing easy code coverage generation.
 *
 * You should type:
 * @code
 *   cmake -DCOVERAGE=ON
 * @endcode 
 * To enable code coverage for this project. To create a coverage report, type:
 * @code
 *   ctest && make coverage
 * @endcode
 * This will create a coverage report in subfolder 'coverage'.
 * 
 */