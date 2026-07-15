cmake_minimum_required(VERSION 4.2)
project(ImageViewer)

if (DEFINED ENV{QT_DIR})
    set(CMAKE_PREFIX_PATH "$ENV{QT_DIR}")
    message(STATUS "Using Qt from environment variable: $ENV{QT_DIR}")
else()
    set(CMAKE_PREFIX_PATH "D:/Qt/6.11.1/mingw_64")
    message(STATUS "Using default Qt path: ${CMAKE_PREFIX_PATH}")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(UI_DIR ${CMAKE_SOURCE_DIR}/ui)

file(GLOB SOURCES "${SRC_DIR}/*.cpp")
file(GLOB HEADERS "${INCLUDE_DIR}/*.h")
file(GLOB UI_FILES "${UI_DIR}/*.ui")

qt6_wrap_ui(UI_HEADERS ${UI_FILES})

include_directories(${INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

qt_add_executable(ImageViewer ${SOURCES} ${HEADERS} ${UI_HEADERS})

target_link_libraries(ImageViewer PRIVATE Qt6::Widgets)

if (WIN32)
    set(EXECUTABLE_DIR "$<TARGET_FILE_DIR:ImageViewer>")
    set(QT_BIN_DIR "${CMAKE_PREFIX_PATH}/bin")
    set(QT_PLUGINS_DIR "${CMAKE_PREFIX_PATH}/plugins")

    add_custom_command(TARGET ImageViewer POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${QT_PLUGINS_DIR}"
            "${EXECUTABLE_DIR}"
            COMMAND ${CMAKE_COMMAND} -E copy
            "${QT_BIN_DIR}/Qt6Core.dll"
            "${EXECUTABLE_DIR}"
            COMMAND ${CMAKE_COMMAND} -E copy
            "${QT_BIN_DIR}/Qt6Gui.dll"
            "${EXECUTABLE_DIR}"
            COMMAND ${CMAKE_COMMAND} -E copy
            "${QT_BIN_DIR}/Qt6Widgets.dll"
            "${EXECUTABLE_DIR}"
    )
endif()