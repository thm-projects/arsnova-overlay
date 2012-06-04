include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

add_definitions(-D__STATIC=static)
add_definitions(-DMAJOR_VERSION=3)
add_definitions(-DMINOR_VERSION=0)
add_definitions(-DMICRO_VERSION=0)
add_definitions(-DVERSION=3)

set(qrencode_SRCS
  libqrencode/qrencode.c
  libqrencode/qrinput.c
  libqrencode/bitstream.c
  libqrencode/qrspec.c
  libqrencode/rscode.c
  libqrencode/split.c
  libqrencode/mask.c
  libqrencode/mqrspec.c
  libqrencode/mmask.c
)

set_source_files_properties(
  ${qrencode_SRCS} PROPERTIES LANGUAGE C
)

add_library(qrencode SHARED
  ${qrencode_SRCS}
)