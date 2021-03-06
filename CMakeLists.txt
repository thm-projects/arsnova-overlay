project(arsnovaoverlay)
cmake_minimum_required(VERSION 2.8.8)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Declarative REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Svg REQUIRED)
find_package(Qt5Test REQUIRED)
find_package(Qt5WebSockets REQUIRED)

# Set current Qt install dir or use param to define it
# set(QTDIR "/Applications/Qt5.5.0/5.5/clang_64/")

set(VERSION_MAJOR 1)
set(VERSION_MINOR 1)
set(VERSION_PATCH dev)

set(VERSION_SHORT ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

if (BUILD_NUMBER)
  set(VERSION_PATCH "${VERSION_PATCH}-${BUILD_NUMBER}")
else(BUILD_NUMBER)
  find_program(GIT_EXECUTABLE "git")
  if(GIT_EXECUTABLE)
    execute_process(
      COMMAND ${GIT_EXECUTABLE} rev-parse --verify -q --short=7 HEAD
      OUTPUT_VARIABLE head
      OUTPUT_STRIP_TRAILING_WHITESPACE
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
    set(VERSION_PATCH "${VERSION_PATCH}-g${head}")
  endif()
endif()

message ("Start build configuration for ARSnova Overlay ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH} ...")
message ("use 'cmake -i' to run CMake in interactive mode")
message ("or use:")
message ("  -DTESTS=(ON|OFF)    to build test application")
message ("  -DCOVERAGE=(ON|OFF) to run test application with code coverage")
message ("")

option (TESTS "Enable build of tests" OFF)
option (COVERAGE "Enable coverage" OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

CONFIGURE_FILE( version.h.cmake src/version.h )
CONFIGURE_FILE( Doxyfile.cmake Doxyfile )
CONFIGURE_FILE( sonar.properties.cmake sonar.properties )
CONFIGURE_FILE( downloadpage-index.html.cmake downloadpage/index.html )

add_custom_target(doc)
find_program(DOXYGEN_EXECUTABLE "doxygen")
if (DOXYGEN_EXECUTABLE)
  add_custom_command(TARGET doc POST_BUILD
    COMMAND ${DOXYGEN_EXECUTABLE}
  )
else(DOXYGEN_EXECUTABLE)
  message ("ERROR: Doxygen not available")
endif(DOXYGEN_EXECUTABLE)

set(DESKTOP
  src/resources/arsnovaoverlay.desktop
)

set(ICONS
  src/resources/arsnova.svg
)

IF (UNIX AND NOT APPLE)
  INSTALL(FILES ${DESKTOP}
    DESTINATION share/applications
  )
  INSTALL(FILES ${ICONS}
    DESTINATION share/icons/hicolor/scalable/apps
  )
ENDIF (UNIX AND NOT APPLE)

if(APPLE)
  set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ";${QTDIR}/lib/cmake;")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
  set(CMAKE_EXE_LINKER_FLAGS "-framework Foundation -w -stdlib=libc++")
endif(APPLE)

if (APPLE OR WIN32)
  add_subdirectory(extern)
endif(APPLE OR WIN32)

add_subdirectory(src)

if(TESTS)
  if (COVERAGE)
    message ("Execute tests with coverage is enabled")
    find_program(LCOV_TOOL "lcov")
    find_program(LCOV_HTML "genhtml")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
  else (COVERAGE)
    message ("Execute tests with coverage is disabled")
  endif(COVERAGE)
  message ("Build of tests is enabled")
  enable_testing()
  add_subdirectory(tests)
else(TESTS)
  message ("Build of tests is disabled")
endif(TESTS)

IF (APPLE)
  INSTALL(FILES ${FILES}
    DESTINATION ../../../
  )
ENDIF (APPLE)

IF (WIN32)
  INSTALL(FILES ${FILES}
    DESTINATION .
  )
  SET(WINQTFILES
    # This part should contain DLL files to be included in package e.g.:
    ${QT_LIBRARY_DIR}/libgcc_s_sjlj-1.dll
    ${QT_LIBRARY_DIR}/libstdc++-6.dll
    ${QT_LIBRARY_DIR}/Qt5Core.dll
    ${QT_LIBRARY_DIR}/Qt5Declarative.dll
    ${QT_LIBRARY_DIR}/Qt5Gui.dll
    ${QT_LIBRARY_DIR}/Qt5Network.dll
    ${QT_LIBRARY_DIR}/Qt5WebSockets.dll
    ${QT_LIBRARY_DIR}/Qt5Widgets.dll
    ${QT_LIBRARY_DIR}/Qt5Script.dll
    ${QT_LIBRARY_DIR}/Qt5Svg.dll
    ${QT_LIBRARY_DIR}/Qt5Sql.dll
    ${QT_LIBRARY_DIR}/Qt5Xml.dll
    ${QT_LIBRARY_DIR}/Qt5XmlPatterns.dll
    ${QT_LIBRARY_DIR}/libEGL.dll
    ${QT_LIBRARY_DIR}/libGLESv2.dll
    ${QT_LIBRARY_DIR}/libharfbuzz-0.dll
    ${QT_LIBRARY_DIR}/icudata56.dll
    ${QT_LIBRARY_DIR}/icui18n56.dll
    ${QT_LIBRARY_DIR}/icuuc56.dll
    ${QT_LIBRARY_DIR}/libpcre16-0.dll
    ${QT_LIBRARY_DIR}/libfreetype-6.dll
    ${QT_LIBRARY_DIR}/libglib-2.0-0.dll
    ${QT_LIBRARY_DIR}/libjpeg-8.dll
    ${QT_LIBRARY_DIR}/libpng16-16.dll
    ${QT_LIBRARY_DIR}/libtiff-5.dll
    ${QT_LIBRARY_DIR}/liblzma-5.dll
    ${QT_LIBRARY_DIR}/zlib1.dll
    ${QT_LIBRARY_DIR}/libssl-10.dll
    ${QT_LIBRARY_DIR}/libcrypto-10.dll
    ${QT_LIBRARY_DIR}/libintl-8.dll
    ${CMAKE_CURRENT_BINARY_DIR}/extern/libqrencode.dll
  )
  INSTALL(FILES ${WINQTFILES}
    DESTINATION .
  )
  INSTALL(FILES
    ${QT_LIBRARY_DIR}/lib/i386-pc/qt5/plugins/platforms/qwindows.dll
    DESTINATION ./platforms
  )
ENDIF (WIN32)

# CPACK
INCLUDE(InstallRequiredSystemLibraries)
SET(CPACK_RESOURCE_FILE_LICENSE  ${CMAKE_CURRENT_SOURCE_DIR}/COPYING)
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "ARSnova Overlay is a small widget to display information taken from arsnova.thm.de")
SET(CPACK_PACKAGE_VENDOR "Paul-Christian Volkmer <paul-christian.volkmer@mni.thm.de>")
SET(CPACK_PACKAGE_CONTACT "Paul-Christian Volkmer <paul-christian.volkmer@mni.thm.de>")
SET(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})
SET(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

IF (UNIX AND NOT APPLE)
  find_program(ARCH_EXECUTABLE "arch")
  if(ARCH_EXECUTABLE)
    execute_process(
      COMMAND ${ARCH_EXECUTABLE}
      OUTPUT_VARIABLE arch
      OUTPUT_STRIP_TRAILING_WHITESPACE
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
    set(CPACK_RPM_PACKAGE_ARCHITECTURE "${arch}")
    SET(CPACK_GENERATOR  "RPM")
  endif()
  # Override architecture if dpkg-architecture command was found on debian based distributions
  find_program(DPKG_EXECUTABLE "dpkg")
  if(DPKG_EXECUTABLE)
    execute_process(
      COMMAND ${DPKG_EXECUTABLE} "--print-architecture"
      OUTPUT_VARIABLE arch
      OUTPUT_STRIP_TRAILING_WHITESPACE
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "${arch}")
    SET(CPACK_GENERATOR  "DEB")
  endif()
  SET(CPACK_SYSTEM_NAME ${CPACK_RPM_PACKAGE_ARCHITECTURE})
  SET(CPACK_RPM_PACKAGE_RELEASE "1")
  SET(CPACK_RPM_PACKAGE_LICENSE "GPLv3")
  SET(
    CPACK_RPM_PACKAGE_DESCRIPTION
    "ARSnova Overlay is a small widget to display information taken from arsnova.thm.de."
  )
  #SET(CPACK_RPM_CHANGELOG_FILE ${CMAKE_CURRENT_BINARY_DIR}/CHANGES)
  SET(CPACK_STRIP_FILES  ${CMAKE_CURRENT_BINARY_DIR}/bin/arsnovaoverlay)

  if (CPACK_GENERATOR STREQUAL "RPM")
    SET(CPACK_PACKAGE_FILE_NAME "arsnovaoverlay-${VERSION}.${arch}")
  elseif(CPACK_GENERATOR STREQUAL "DEB")
    SET(CPACK_PACKAGE_FILE_NAME "arsnovaoverlay_${VERSION}_${arch}")
  endif()
ENDIF (UNIX AND NOT APPLE)

IF (WIN32)
  SET(CPACK_GENERATOR  "NSIS")
  SET(CPACK_SYSTEM_NAME "win32")
  SET(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_BINARY_DIR}/COPYING)
  SET(CPACK_NSIS_MODIFY_PATH OFF)
  SET(CPACK_NSIS_PACKAGE_NAME "ARSnova Overlay")
  SET(CPACK_NSIS_DISPLAY_NAME "ARSnova Overlay")
  SET(CPACK_NSIS_CONTACT "${CPACK_PACKAGE_VENDOR}")
  SET(CPACK_NSIS_URL_INFO_ABOUT "https:\\\\\\\\arsnova.eu\\\\blog\\\\")
  SET(CPACK_NSIS_MUI_FINISHPAGE_RUN "arsnovaoverlay.exe")
  SET(CPACK_PACKAGE_ICON ${CMAKE_CURRENT_BINARY_DIR}/src/resources/images/logo_32.png)
  SET(CPACK_PACKAGE_EXECUTABLES  ..\\\\arsnovaoverlay;ARSnovaOverlay)
  SET(CPACK_CREATE_DESKTOP_LINKS ..\\\\arsnovaoverlay)
  SET(CPACK_PACKAGE_INSTALL_DIRECTORY "ARSnova Overlay")
  SET(CPACK_STRIP_FILES  ${CMAKE_CURRENT_BINARY_DIR}/bin/arsnovaoverlay.exe)
ENDIF (WIN32)

IF (APPLE)
  SET(CPACK_GENERATOR  "Bundle")
  SET(CPACK_BUNDLE_NAME "ARSnovaOverlay")
  SET(CPACK_BUNDLE_PLIST ${CMAKE_CURRENT_BINARY_DIR}/Info.plist)
  SET(CPACK_BUNDLE_ICON ${CMAKE_CURRENT_BINARY_DIR}/src/resources/images/arsnovaoverlay.icns)
ENDIF (APPLE)

INCLUDE(CPack)
