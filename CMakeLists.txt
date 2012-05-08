project(arsnovawidget)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)

if(APPLE)
  set(CMAKE_EXE_LINKER_FLAGS "-framework Foundation -w")
endif(APPLE)

add_subdirectory(src)
add_subdirectory(test)
