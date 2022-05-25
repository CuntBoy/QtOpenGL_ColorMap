cmake_minimum_required(VERSION 3.5)

project(QtOpenGL_ColorMap LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(QRC_SOURCE_FILES resources/colorMap.qrc)

find_package(Qt5 REQUIRED COMPONENTS Widgets OpenGL LinguistTools)

qt5_add_resources(QRC_FILES ${QRC_SOURCE_FILES})

# 语言文件
# set(TS_FILES QtOpenGL_ColorMap_zh_CN.ts)

# SET(RESOURCES_FILE colorMap.qrc)

SET(HEADERS
    src/base/colorscale.h
    src/base/coordinatesystem.h
    src/base/drawdata.h
    src/base/mainwindow.h
    src/base/windowcenterwidget.h
    src/colormap/colormapwidget.h
    src/colormap/colormapdata.h
    src/colormap/colormapcoordinate.h
    src/colormap/colormapcolorscale.h
    src/colormap/colormap.h
)

SET(SOURCES
    src/base/colorscale.cpp
    src/base/coordinatesystem.cpp
    src/base/drawdata.cpp
    src/base/mainwindow.cpp
    src/base/windowcenterwidget.cpp
    src/colormap/colormapwidget.cpp
    src/colormap/colormapdata.cpp
    src/colormap/colormapcoordinate.cpp
    src/colormap/colormapcolorscale.cpp
    src/colormap/colormap.cpp
)

LIST(APPEND INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/src)
add_executable(QtOpenGL_ColorMap
    main.cpp
    ${SOURCES}
    ${HEADERS}
    ${TS_FILES}
    ${QRC_FILES}
)

target_include_directories(QtOpenGL_ColorMap PRIVATE ${INCLUDE_DIRECTORIES})
target_link_libraries(QtOpenGL_ColorMap PRIVATE Qt5::Widgets Qt5::OpenGL)

# qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
