include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(arsnovawidget_SRCS
  ui/mainwindow.cpp
  ui/overlaywidget.cpp
  ui/qrcodewidget.cpp
  ui/sessionwidget.cpp
  ui/systemtrayicon.cpp
  ui/settingswidget.cpp
  updatetimer.cpp
  httpconnection.cpp
  sessionresponse.cpp
  feedbackresponse.cpp
  loggedinresponse.cpp
  svglogo.cpp
  qplugin/loginwidget.cpp
  qplugin/bardiagramwidget.cpp
  qplugin/logodiagramwidget.cpp
  qplugin/emotediagramwidget.cpp
  qplugin/sessioninformationwidget.cpp
  qrcodegenerator.cpp
  interposedquestion.cpp
  sessioncontext.cpp
  settings.cpp
  main.cpp
)

set(arsnovawidgetplugin_SRCS
  svglogo.cpp
  feedbackresponse.cpp
  qplugin/arsnovawidgetcollection.cpp
  qplugin/loginwidget.cpp
  qplugin/loginwidgetplugin.cpp
  qplugin/bardiagramwidget.cpp
  qplugin/bardiagramwidgetplugin.cpp
  qplugin/logodiagramwidget.cpp
  qplugin/logodiagramwidgetplugin.cpp
  qplugin/emotediagramwidget.cpp
  qplugin/emotediagramwidgetplugin.cpp
  qplugin/sessioninformationwidget.cpp
  qplugin/sessioninformationwidgetplugin.cpp
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
  ui/mainwindow.h
  ui/overlaywidget.h
  ui/qrcodewidget.h
  ui/sessionwidget.h
  ui/systemtrayicon.h
  ui/settingswidget.h
  updatetimer.h
  abstractconnection.h
  httpconnection.h
  sessionresponse.h
  feedbackresponse.h
  loggedinresponse.h
  svglogo.h
  qplugin/loginwidget.h
  qplugin/bardiagramwidget.h
  qplugin/logodiagramwidget.h
  qplugin/emotediagramwidget.h
  qplugin/sessioninformationwidget.h
  qrcodegenerator.h
  interposedquestion.h
  sessioncontext.h
)

set(arsnovawidgetplugin_MOC_SRCS
  qplugin/arsnovawidgetcollection.h
  qplugin/loginwidget.h
  qplugin/loginwidgetplugin.h
  qplugin/bardiagramwidget.h
  qplugin/bardiagramwidgetplugin.h
  qplugin/logodiagramwidget.h
  qplugin/logodiagramwidgetplugin.h
  qplugin/emotediagramwidget.h
  qplugin/emotediagramwidgetplugin.h
  qplugin/sessioninformationwidget.h
  qplugin/sessioninformationwidgetplugin.h
)

set(arsnovawidget_UIS
  ui/mainwindow.ui
  ui/overlaywidget.ui
  ui/qrcodewidget.ui
  ui/sessionwidget.ui
  ui/sessionwidget.ui
)

set(arsnovawidgetplugin_UIS
  qplugin/emotediagramwidget.ui
  qplugin/logodiagramwidget.ui
  qplugin/sessioninformationwidget.ui
)

## Resources ##
set(resources_RCCS
  resources/resources.qrc
)

qt4_add_resources(resources_RCC_SRCS ${resources_RCCS})
#####

qt4_wrap_cpp(arsnovawidget_SRCS ${arsnovawidget_MOC_SRCS})
qt4_wrap_ui(arsnovawidget_UIS_H ${arsnovawidget_UIS} ${arsnovawidgetplugin_UIS})

qt4_wrap_cpp(arsnovawidgetplugin_SRCS ${arsnovawidgetplugin_MOC_SRCS})
qt4_wrap_ui(arsnovawidgetplugin_UIS_H ${arsnovawidgetplugin_UIS})

IF( WIN32 AND MINGW )
  # To cross compile on Linux use: 'i686-w64-mingw32-windres' or similar command shipped with mingw cross compiler.
  # Change resources/arsnovawidgeticon.rc to use the correct path seperator depending on used plattform.
  ADD_CUSTOM_COMMAND( OUTPUT arsnovawidgeticon.rc.obj
    COMMAND i686-w64-mingw32-windres -I${CMAKE_CURRENT_SOURCE_DIR} -i${CMAKE_CURRENT_SOURCE_DIR}/resources/arsnovawidgeticon.rc 
	-o arsnovawidgeticon.rc.obj
  )
  SET(arsnovawidget_SRCS ${arsnovawidget_SRCS} ${CMAKE_CURRENT_BINARY_DIR}/arsnovawidgeticon.rc.obj)
ENDIF( WIN32 AND MINGW )

IF( WIN32 AND NOT MINGW )
  SET(arsnovawidget_SRCS ${arsnovawidget_SRCS} arsnovawidgeticon.rc)
ENDIF( WIN32 AND NOT MINGW )

add_executable(arsnovadesktop MACOSX_BUNDLE WIN32
  ${arsnovawidget_SRCS}
  ${arsnovawidget_UIS_H}
  ${resources_RCC_SRCS}
)

if(QTPLUGIN)
  add_library(qarsnova SHARED
    ${arsnovawidgetplugin_SRCS}
    ${arsnovawidgetplugin_UIS_H}
    ${resources_RCC_SRCS}
  )
endif(QTPLUGIN)

target_link_libraries(arsnovadesktop
  ${QT_QTCORE_LIBRARY}
  ${QT_QTGUI_LIBRARY}
  ${QT_QTNETWORK_LIBRARY}
  ${QT_QTSCRIPT_LIBRARY}
  ${QT_QTSVG_LIBRARY}
  ${QT_QTDECLARATIVE_LIBRARY}
  qrencode
)

if(QTPLUGIN)
  target_link_libraries(qarsnova
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${QT_QTSVG_LIBRARY}
    ${QT_QTDECLARATIVE_LIBRARY}
  )
endif(QTPLUGIN)

IF(APPLE)
  SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmacosx-version-min=10.7") 
  INSTALL(CODE
    "SET(BUNDLE
      \"\${CMAKE_INSTALL_PREFIX}/../..\"
    )"
  )
  INSTALL(CODE "EXECUTE_PROCESS(COMMAND macdeployqt ./bin/arsnovadesktop.app)")
  INSTALL(TARGETS arsnovadesktop BUNDLE DESTINATION ../../../)
ENDIF(APPLE)

IF (UNIX AND NOT APPLE)
  INSTALL(TARGETS arsnovadesktop
    RUNTIME DESTINATION bin
  )
ENDIF (UNIX AND NOT APPLE)

IF (WIN32)
  INSTALL(TARGETS arsnovadesktop
    RUNTIME DESTINATION .
  )
ENDIF (WIN32)