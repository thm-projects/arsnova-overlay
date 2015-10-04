include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(arsnovawidget_SRCS
  ui/mainwindow.cpp
  ui/overlaywidget.cpp
  ui/qrcodewidget.cpp
  ui/sessionwidget.cpp
  ui/systemtrayicon.cpp
  ui/settingswidget.cpp
  ui/infodialog.cpp
  updatetimer.cpp
  httpconnection.cpp
  sessionresponse.cpp
  feedbackresponse.cpp
  loggedinresponse.cpp
  audiencequestioncountresponse.cpp
  svglogo.cpp
  ui/loginwidget.cpp
  ui/bardiagramwidget.cpp
  ui/logodiagramwidget.cpp
  ui/emotediagramwidget.cpp
  ui/sessioninformationwidget.cpp
  qrcodegenerator.cpp
  interposedquestion.cpp
  sessioncontext.cpp
  abstractconnection.cpp
  settings.cpp
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
  ui/mainwindow.h
  ui/overlaywidget.h
  ui/qrcodewidget.h
  ui/sessionwidget.h
  ui/systemtrayicon.h
  ui/settingswidget.h
  ui/infodialog.h
  updatetimer.h
  abstractconnection.h
  httpconnection.h
  sessionresponse.h
  feedbackresponse.h
  loggedinresponse.h
  audiencequestioncountresponse.h
  svglogo.h
  ui/loginwidget.h
  ui/bardiagramwidget.h
  ui/logodiagramwidget.h
  ui/emotediagramwidget.h
  ui/sessioninformationwidget.h
  qrcodegenerator.h
  interposedquestion.h
  sessioncontext.h
  settings.h
)

set(arsnovawidget_UIS
  ui/mainwindow.ui
  ui/overlaywidget.ui
  ui/qrcodewidget.ui
  ui/sessionwidget.ui
  ui/settingswidget.ui
  ui/infodialog.ui
  ui/emotediagramwidget.ui
  ui/logodiagramwidget.ui
)

## Resources ##
set(resources_RCCS
  resources/resources.qrc
)

qt5_add_resources(resources_RCC_SRCS ${resources_RCCS})
#####

#qt5_wrap_cpp(arsnovawidget_SRCS ${arsnovawidget_MOC_SRCS})
qt5_wrap_ui(arsnovawidget_UIS_H ${arsnovawidget_UIS} ${arsnovawidgetplugin_UIS})

IF( WIN32 AND MINGW )
  # To cross compile on Linux use: 'i686-w64-mingw32-windres' or similar command shipped with mingw cross compiler.
  # Change resources/arsnovaoverlayicon.rc to use the correct path seperator depending on used plattform.
  ADD_CUSTOM_COMMAND( OUTPUT arsnovaoverlayicon.rc.obj
    COMMAND i686-w64-mingw32-windres -I${CMAKE_CURRENT_SOURCE_DIR} -i${CMAKE_CURRENT_SOURCE_DIR}/resources/arsnovaoverlayicon.rc 
	-o arsnovaoverlayicon.rc.obj
  )
  SET(arsnovawidget_SRCS ${arsnovawidget_SRCS} ${CMAKE_CURRENT_BINARY_DIR}/arsnovaoverlayicon.rc.obj)
ENDIF( WIN32 AND MINGW )

IF( WIN32 AND NOT MINGW )
  SET(arsnovawidget_SRCS ${arsnovawidget_SRCS} arsnovaoverlayicon.rc)
ENDIF( WIN32 AND NOT MINGW )

add_executable(arsnovaoverlay MACOSX_BUNDLE WIN32
  ${arsnovawidget_SRCS}
  ${arsnovawidget_UIS_H}
  ${resources_RCC_SRCS}
)

qt5_use_modules(arsnovaoverlay Core Widgets Declarative Network Svg WebSockets)

target_link_libraries(arsnovaoverlay
  qrencode
)

IF(APPLE)
  SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmacosx-version-min=10.7") 
  INSTALL(CODE
    "SET(BUNDLE
      \"\${CMAKE_INSTALL_PREFIX}/../..\"
    )"
  )
  INSTALL(CODE "EXECUTE_PROCESS(COMMAND ${QTDIR}/macdeployqt ${CMAKE_CURRENT_SOURCE_DIR}/arsnovaoverlay.app)")
  INSTALL(TARGETS arsnovaoverlay BUNDLE DESTINATION ../../../)
ENDIF(APPLE)

IF (UNIX AND NOT APPLE)
  INSTALL(TARGETS arsnovaoverlay
    RUNTIME DESTINATION bin
  )
ENDIF (UNIX AND NOT APPLE)

IF (WIN32)
  INSTALL(TARGETS arsnovaoverlay
    RUNTIME DESTINATION .
  )
ENDIF (WIN32)