include_directories(
  ${QT_INCLUDES}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/../src/
)

set(arsnovawidget_SRCS
  ../src/svglogo.cpp
  svglogotest.cpp
  ../src/feedbackresponse.cpp
  ../src/qplugin/loginwidget.cpp
  qplugin/loginwidgettest.cpp
  ../src/qplugin/bardiagramwidget.cpp
  qplugin/bardiagramwidgettest.cpp
  ../src/qplugin/logodiagramwidget.cpp
  qplugin/logodiagramwidgettest.cpp
  ../src/qplugin/emotediagramwidget.cpp
  qplugin/emotediagramwidgettest.cpp
  ../src/qplugin/sessioninformationwidget.cpp
  qplugin/sessioninformationwidgettest.cpp
  ../src/ui/overlaywidget.cpp
  ui/overlaywidgettest.cpp
  ../src/ui/qrcodewidget.cpp
  ui/mainwindowtest.cpp
  ../src/ui/mainwindow.cpp
  ../src/ui/sessionwidget.cpp
  ui/sessionwidgettest.cpp
  ui/qrcodewidgettest.cpp
  ../src/updatetimer.cpp
  ../src/httpconnection.cpp
  stubconnection.cpp
  ../src/sessionresponse.cpp
  ../src/loggedinresponse.cpp
  ../src/qrcodegenerator.cpp
  ../src/interposedquestion.cpp
  ../src/sessioncontext.cpp
  sessioncontexttest.cpp
  ../src/ui/systemtrayicon.cpp
  ui/systemtrayicontest.cpp
  ../src/abstractconnection.cpp
  feedbackresponsetest.cpp
  ../src/ui/settingswidget.cpp
  ../src/settings.cpp
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
  ../src/feedbackresponse.h
  ../src/qplugin/loginwidget.h
  qplugin/loginwidgettest.h
  ../src/qplugin/bardiagramwidget.h
  qplugin/bardiagramwidgettest.h
  ../src/qplugin/logodiagramwidget.h
  qplugin/logodiagramwidgettest.h
  ../src/qplugin/emotediagramwidget.h
  qplugin/emotediagramwidgettest.h
  ../src/qplugin/sessioninformationwidget.h
  qplugin/sessioninformationwidgettest.h
  ../src/ui/overlaywidget.h
  ui/overlaywidgettest.h
  ../src/ui/qrcodewidget.h
  ui/mainwindowtest.h
  ../src/ui/mainwindow.h
  ../src/ui/sessionwidget.h
  ui/sessionwidgettest.h
  ui/qrcodewidgettest.h
  ../src/updatetimer.h
  ../src/abstractconnection.h
  ../src/httpconnection.h
  stubconnection.h
  ../src/sessionresponse.h
  ../src/loggedinresponse.h
  ../src/qrcodegenerator.h
  ../src/interposedquestion.h
  ../src/sessioncontext.h
  sessioncontexttest.h
  ../src/ui/systemtrayicon.h
  ui/systemtrayicontest.h
  feedbackresponsetest.h
  ../src/ui/settingswidget.h
  ../src/settings.h
)

set(arsnovawidget_UIS
  ../src/qplugin/logodiagramwidget.ui
  ../src/qplugin/emotediagramwidget.ui
  ../src/qplugin/sessioninformationwidget.ui
  ../src/ui/overlaywidget.ui
  ../src/ui/sessionwidget.ui
  ../src/ui/settingswidget.ui
)

## Resources ##
set(resources_RCCS
  ../src/resources/resources.qrc
)

qt5_add_resources(resources_RCC_SRCS ${resources_RCCS})
#####

#qt5_wrap_cpp(arsnovawidget_SRCS ${arsnovawidget_MOC_SRCS})
qt5_wrap_ui(arsnovawidget_UIS_H ${arsnovawidget_UIS})

add_executable(tests
  ${arsnovawidget_SRCS}
  ${arsnovawidget_UIS_H}
  ${resources_RCC_SRCS}
)

qt5_use_modules(tests Core Widgets Declarative Network Svg Test)

target_link_libraries(tests
  #${QT_QTCORE_LIBRARY}
  #${QT_QTGUI_LIBRARY}
  #${QT_QTNETWORK_LIBRARY}
  #${QT_QTSCRIPT_LIBRARY}
  #${QT_QTSVG_LIBRARY}
  #${QT_QTTEST_LIBRARY}
  #${QT_QTTESTGUI_LIBRARY}
  #${QT_QTDECLARATIVE_LIBRARY}
  qrencode
)

if (TESTS AND COVERAGE)
add_custom_target(coverage)
add_dependencies(coverage check)

add_custom_command(TARGET coverage POST_BUILD
  COMMAND ${LCOV_TOOL} --directory ${CMAKE_CURRENT_BINARY_DIR}/ --capture --output-file coverage.info
  COMMAND ${LCOV_TOOL} --remove coverage.info .cxx -o coverage.info
  COMMAND ${LCOV_TOOL} --remove coverage.info *include* -o coverage.info
  COMMAND ${LCOV_TOOL} --remove coverage.info *extern* -o coverage.info

  COMMAND ${LCOV_HTML} coverage.info --no-branch-coverage -o ${CMAKE_CURRENT_BINARY_DIR}/../coverage

  COMMAND ${LCOV_TOOL} --directory ${CMAKE_CURRENT_BINARY_DIR}/../ --zerocounters
)  
endif (TESTS AND COVERAGE)

add_test(SvgLogoTest ${EXECUTABLE_OUTPUT_PATH}/tests SvgLogoTest)
add_test(LoginWidgetTest ${EXECUTABLE_OUTPUT_PATH}/tests LoginWidgetTest)
add_test(BarDiagramWidgetTest ${EXECUTABLE_OUTPUT_PATH}/tests BarDiagramWidgetTest)
add_test(LogoDiagramWidgetTest ${EXECUTABLE_OUTPUT_PATH}/tests LogoDiagramWidgetTest)
add_test(EmoteDiagramWidgetTest ${EXECUTABLE_OUTPUT_PATH}/tests EmoteDiagramWidgetTest)
add_test(OverlayWidgetTest ${EXECUTABLE_OUTPUT_PATH}/tests OverlayWidgetTest)
add_test(SessionInformationWidgetTest ${EXECUTABLE_OUTPUT_PATH}/tests SessionInformationWidgetTest)
add_test(QRCodeWidgetTest ${EXECUTABLE_OUTPUT_PATH}/tests QRCodeWidgetTest)
add_test(MainWindowTest ${EXECUTABLE_OUTPUT_PATH}/tests MainWindowTest)
add_test(SessionContextTest ${EXECUTABLE_OUTPUT_PATH}/tests SessionContextTest)
add_test(SystemTrayIconTest ${EXECUTABLE_OUTPUT_PATH}/tests SystemTrayIconTest)
add_test(SessionWidgetTest ${EXECUTABLE_OUTPUT_PATH}/tests SessionWidgetTest)
add_test(FeedbackResponseTest ${EXECUTABLE_OUTPUT_PATH}/tests FeedbackResponseTest)
