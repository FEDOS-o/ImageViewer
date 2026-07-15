cmake_minimum_required(VERSION 4.2)
project(ImageViewer)

set(CMAKE_PREFIX_PATH "D:\\Qt\\6.11.1\\mingw_64")

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

    # Просто копируем всё необходимое
    add_custom_command(TARGET ImageViewer POST_BUILD
            # Копируем плагины
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_PREFIX_PATH}/plugins"
            "${EXECUTABLE_DIR}"
            # Копируем DLL
            COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_PREFIX_PATH}/bin/Qt6Core.dll"
            "${EXECUTABLE_DIR}"
            COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_PREFIX_PATH}/bin/Qt6Gui.dll"
            "${EXECUTABLE_DIR}"
            COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_PREFIX_PATH}/bin/Qt6Widgets.dll"
            "${EXECUTABLE_DIR}"
    )
endif()