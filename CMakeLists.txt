cmake_minimum_required(VERSION 3.5)

project(QtOpenGL_ColorMap LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets OpenGL LinguistTools REQUIRED)

# 语言文件
set(TS_FILES QtOpenGL_ColorMap_zh_CN.ts)

SET(RESOURCES_FILE colorMap.qrc)

SET(HEADERS
    base/colorscale.h
    base/coordinatesystem.h
    base/drawdata.h
    base/mainwindow.h
    base/windowcenterwidget.h
    colormap/colormapwidget.h
    colormap/colormapdata.h
    colormap/colormapcoordinate.h
    colormap/colormapcolorscale.h
    colormap/colormap.h
)

SET(SOURCES
    base/colorscale.cpp
    base/coordinatesystem.cpp
    base/drawdata.cpp
    base/mainwindow.cpp
    base/windowcenterwidget.cpp
    colormap/colormapwidget.cpp
    colormap/colormapdata.cpp
    colormap/colormapcoordinate.cpp
    colormap/colormapcolorscale.cpp
    colormap/colormap.cpp
)

if(ANDROID)
  add_library(QtOpenGL_ColorMap SHARED
    main.cpp
    ${TS_FILES}
  )
else()
  add_executable(QtOpenGL_ColorMap
    main.cpp
    ${SOURCES}
    #${HEADERS}
    ${TS_FILES}
    ${RESOURCES_FILE}
  )
endif()

target_link_libraries(QtOpenGL_ColorMap PRIVATE Qt5::Widgets Qt5::OpenGL)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
