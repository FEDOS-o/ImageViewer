cmake_minimum_required(VERSION 4.2)
project(ImageViewer)

set(CMAKE_PREFIX_PATH "D:\\Qt\\6.11.1\\mingw_64")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF)  # ← ОТКЛЮЧАЕМ AUTOUIC

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(UI_DIR ${CMAKE_SOURCE_DIR}/ui)

file(GLOB SOURCES "${SRC_DIR}/*.cpp")
file(GLOB HEADERS "${INCLUDE_DIR}/*.h")

# Явно находим .ui файлы
file(GLOB UI_FILES "${UI_DIR}/*.ui")

# Явно генерируем ui_*.h из .ui файлов
qt6_wrap_ui(UI_HEADERS ${UI_FILES})

include_directories(${INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})  # Для сгенерированных ui_*.h

qt_add_executable(ImageViewer ${SOURCES} ${HEADERS} ${UI_HEADERS})

target_link_libraries(ImageViewer PRIVATE Qt6::Widgets)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()