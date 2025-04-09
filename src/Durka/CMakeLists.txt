cmake_minimum_required(VERSION 3.16)

project(Durka VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 COMPONENTS Core Quick Qml Widgets REQUIRED)

add_executable( durkaApp
		main.cpp
)

add_subdirectory( qml )

#target_compile_definitions(Durka
#  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries( Durka
  PRIVATE Qt6::Core
  Qt6::Quick
  Qt6:Qml
  Qt6::Widgets
  DurkaQmlLibplugin
)

install(
		BUNDLE DESTINATION .
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

