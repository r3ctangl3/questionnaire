cmake_minimum_required(VERSION 3.16)

project(try2build_qrc VERSION 1.0 LANGUAGES CXX)

set(TARGET_NAME "TestLab")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set( CMAKE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ) #Contains cmake support functions
set( QML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/qml" ) #Contains QML files

find_package(Qt6 6.2 COMPONENTS Quick Widgets REQUIRED)

#include cmake files
file(GLOB CMAKE_FILES "${CMAKE_DIR}/*.cmake")
include( ${CMAKE_FILES} )

#include h files
file(GLOB_RECURSE HEADER_FILES "dev/*.h" "dev/*.hpp")
#include cpp files
file(GLOB_RECURSE SOURCE_FILES "dev/*.cpp")

qt_add_executable(${TARGET_NAME}
        main.cpp
)

target_sources(${TARGET_NAME}
        PUBLIC ${HEADER_FILES}
        PRIVATE ${SOURCE_FILES}
)

#Create directory for QRC file
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/generated_sources)
#declare qrc file path
set(QRC_FILE_PATH "${CMAKE_CURRENT_BINARY_DIR}/generated_sources/generated_qml.qrc")

#generate qml sources
generate_qml_qrc(
        TARGET_NAME ${TARGET_NAME}
        QML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/qml"
        RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources"
        OUTPUT_QRC "${QRC_FILE_PATH}"
        QML_PREFIX "/ui"
        RESOURCES_PREFIX "/style"
)


target_link_libraries(${TARGET_NAME}
        PRIVATE Qt6::Quick Qt6::Widgets
)

set_target_properties(${TARGET_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(${TARGET_NAME}
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)

#В production QML Debugging должен быть отключён (злоумышленники могут использовать его для инъекций).



