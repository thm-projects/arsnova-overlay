include_directories(
  ${QT_INCLUDES}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/../src/
)

set(arsnovawidget_SRCS
  ../src/svglogo.cpp
  svglogotest.cpp
  ../src/understandingresponse.cpp
  ../src/qplugin/loginwidget.cpp
  qplugin/loginwidgettest.cpp
  main.cpp
)

set(arsnovawidget_MAC_SRCS
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
  ../src/svglogo.h
  svglogotest.h
  ../src/understandingresponse.h
  ../src/qplugin/loginwidget.h
  qplugin/loginwidgettest.h
)

set(arsnovawidget_UIS
  ../src/qplugin/loginwidget.ui
)

## Resources ##
set(resources_RCCS
  ../src/resources/resources.qrc
)

qt4_add_resources(resources_RCC_SRCS ${resources_RCCS})
#####

qt4_wrap_cpp(arsnovawidget_SRCS ${arsnovawidget_MOC_SRCS})
qt4_wrap_ui(arsnovawidget_UIS_H ${arsnovawidget_UIS})

add_executable(tests
  ${arsnovawidget_SRCS}
  ${arsnovawidget_UIS_H}
  ${resources_RCC_SRCS}
)

target_link_libraries(tests
  ${QT_QTCORE_LIBRARY}
  ${QT_QTGUI_LIBRARY}
  ${QT_QTNETWORK_LIBRARY}
  ${QT_QTSCRIPT_LIBRARY}
  ${QT_QTSVG_LIBRARY}
  ${QT_QTTEST_LIBRARY}
  ${QT_QTTESTGUI_LIBRARY}
)

add_test(SvgLogoTest ${EXECUTABLE_OUTPUT_PATH}/tests SvgLogoTest)
add_test(LoginWidgetTest ${EXECUTABLE_OUTPUT_PATH}/tests LoginWidgetTest)
