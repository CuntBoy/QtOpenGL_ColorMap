cmake_minimum_required(VERSION 3.5)

SET(ProjectName ColorMap)

project(${ProjectName} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(QRC_SOURCE_FILES resources/colorMap.qrc)

# 三方库目录
SET(INC_DIR  ${CMAKE_SOURCE_DIR}/liberaries/include)
SET(LINK_DIR ${CMAKE_SOURCE_DIR}/liberaries/lib)
message (STATUS " INC_DIR " ${INC_DIR})
message (STATUS " LINK_DIR " ${LINK_DIR})
include_directories(${INC_DIR})
link_directories(${LINK_DIR})

# find_package(freetype REQUIRED COMPONENTS freetype)
#if(freetype_FOUND)
#    message ("freetype found")
#    message (STATUS " ==> " ${freetype_DIR})
#else()
#    message (FATAL_ERROR "Cannot find freetype")
#endif()

find_package(Qt5 REQUIRED COMPONENTS Widgets OpenGL LinguistTools)

qt5_add_resources(QRC_FILES ${QRC_SOURCE_FILES})

# 语言文件
# set(TS_FILES QtOpenGL_ColorMap_zh_CN.ts)

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
    src/colormap/RenderThread.h
    src/base/glfont.h
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
    src/colormap/RenderThread.cpp
    src/base/character.h  # 字符文件
    src/base/glfont.cpp 
    src/base/character.cpp
    
)

LIST(APPEND INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/src)
LIST(APPEND INCLUDE_DIRECTORIES ${INC_DIR})

add_executable(${ProjectName}
    main.cpp
    ${SOURCES}
    ${HEADERS}
    ${TS_FILES}
    ${QRC_FILES}
  )

target_include_directories(${ProjectName} PRIVATE ${INCLUDE_DIRECTORIES})
target_link_libraries(${ProjectName} PRIVATE Qt5::Widgets Qt5::OpenGL freetype)

# qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
