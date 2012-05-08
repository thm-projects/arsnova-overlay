include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(arsnovawidget_SRCS
  ui/overlaywidget.cpp
  updatetimer.cpp
  main.cpp
)

set(arsnovawidget_MAC_SRCS
  main.m
)

set_source_files_properties(
  ${arsnovawidget_MAC_SRCS} PROPERTIES LANGUAGE C
)

if(APPLE)
  set(arsnovawidget_SRCS
    ${arsnovawidget_SRCS}
    ${arsnovawidget_MAC_SRCS}
  )
endif(APPLE)

set(arsnovawidget_MOC_SRCS
  ui/overlaywidget.h
  updatetimer.h
)

set(arsnovawidget_UIS
  ui/overlaywidget.ui
)

## Resources ##
set(resources_RCCS
  resources/resources.qrc
)

qt4_add_resources(resources_RCC_SRCS ${resources_RCCS})
#####

qt4_wrap_cpp(arsnovawidget_SRCS ${arsnovawidget_MOC_SRCS})
qt4_wrap_ui(arsnovawidget_UIS_H ${arsnovawidget_UIS})

add_executable(arsnovawidget
  ${arsnovawidget_SRCS}
  ${arsnovawidget_UIS_H}
  ${resources_RCC_SRCS}
)

target_link_libraries(arsnovawidget
  ${QT_QTCORE_LIBRARY}
  ${QT_QTGUI_LIBRARY}
  ${QT_QTNETWORK_LIBRARY}
  ${QT_QTSCRIPT_LIBRARY}
)