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
  ../src/qplugin/bardiagramwidget.cpp
  qplugin/bardiagramwidgettest.cpp
  ../src/qplugin/logodiagramwidget.cpp
  qplugin/logodiagramwidgettest.cpp
  ../src/qplugin/sessioninformationwidget.cpp
  qplugin/sessioninformationwidgettest.cpp
  ../src/ui/overlaywidget.cpp
  ../src/ui/qrcodewidget.cpp
  ui/overlaywidgettest.cpp
  ../src/updatetimer.cpp
  ../src/httpconnection.cpp
  stubconnection.cpp
  ../src/sessionresponse.cpp
  ../src/loggedinresponse.cpp
  ../src/qrcodegenerator.cpp
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
  ../src/qplugin/bardiagramwidget.h
  qplugin/bardiagramwidgettest.h
  ../src/qplugin/logodiagramwidget.h
  qplugin/logodiagramwidgettest.h
  ../src/qplugin/sessioninformationwidget.h
  qplugin/sessioninformationwidgettest.h
  ../src/ui/overlaywidget.h
  ../src/ui/qrcodewidget.h
  ui/overlaywidgettest.h
  ../src/updatetimer.h
  ../src/abstractconnection.h
  ../src/httpconnection.h
  stubconnection.h
  ../src/sessionresponse.h
  ../src/loggedinresponse.h
  ../src/qrcodegenerator.h
)

set(arsnovawidget_UIS
  ../src/qplugin/loginwidget.ui
  ../src/qplugin/bardiagramwidget.ui
  ../src/qplugin/logodiagramwidget.ui
  ../src/qplugin/sessioninformationwidget.ui
  ../src/ui/overlaywidget.ui
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
  qrencode
)

if (TESTS AND COVERAGE)
add_custom_target(coverage)
add_dependencies(coverage check)

add_custom_command(TARGET coverage POST_BUILD
  COMMAND ${LCOV_TOOL} --directory ${CMAKE_CURRENT_BINARY_DIR}/ --capture --output-file coverage.info
  COMMAND ${LCOV_TOOL} --remove coverage.info .cxx -o coverage.info
  COMMAND ${LCOV_TOOL} --remove coverage.info *include* -o coverage.info

  COMMAND ${LCOV_HTML} coverage.info --no-branch-coverage -o ${CMAKE_CURRENT_BINARY_DIR}/../coverage

  COMMAND ${LCOV_TOOL} --directory ${CMAKE_CURRENT_BINARY_DIR}/../ --zerocounters
)  
endif (TESTS AND COVERAGE)

add_test(SvgLogoTest ${EXECUTABLE_OUTPUT_PATH}/tests SvgLogoTest)
add_test(LoginWidgetTest ${EXECUTABLE_OUTPUT_PATH}/tests LoginWidgetTest)
add_test(BarDiagramWidgetTest ${EXECUTABLE_OUTPUT_PATH}/tests BarDiagramWidgetTest)
add_test(LogoDiagramWidgetTest ${EXECUTABLE_OUTPUT_PATH}/tests LogoDiagramWidgetTest)
add_test(OverlayWidgetTest ${EXECUTABLE_OUTPUT_PATH}/tests OverlayWidgetTest)
add_test(SessionInformationWidgetTest ${EXECUTABLE_OUTPUT_PATH}/tests SessionInformationWidgetTest)