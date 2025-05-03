cmake_minimum_required(VERSION 3.16)

project(try2build_qrc VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set( CMAKE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ) #Contains cmake support functions
set( QML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/qml" ) #Contains QML files

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

#include cmake files
file(GLOB CMAKE_FILES "${CMAKE_DIR}/*.cmake")
include( ${CMAKE_FILES} )

qt_add_executable(${PROJECT_NAME}
        main.cpp
)

#Create directory for QRC file
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/generated_sources)
#declare qrc file path
set(QRC_FILE_PATH "${CMAKE_CURRENT_BINARY_DIR}/generated_sources/generated_qml.qrc")

generate_qml_qrc(
        TARGET_NAME ${PROJECT_NAME}
        QML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/qml"
        OUTPUT_QRC "${QRC_FILE_PATH}"
        PREFIX "/"
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE Qt6::Quick
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)

#В production QML Debugging должен быть отключён (злоумышленники могут использовать его для инъекций).



