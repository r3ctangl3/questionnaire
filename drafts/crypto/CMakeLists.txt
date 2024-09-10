cmake_minimum_required(VERSION 3.16)

project(GuiApp VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Sql)               # Required for SQL drivers work


add_subdirectory(chacha20)


set(PROJECT_SOURCES
    main.cpp
    crypto.cpp
    crypto.h
    database.cpp
    database.h
    database_structure.cpp
    utils.h
    widget.cpp
    widget.h
)

qt_add_executable(GuiApp MANUAL_FINALIZATION ${PROJECT_SOURCES})


target_link_libraries(GuiApp PRIVATE chacha20)
target_link_libraries(GuiApp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(GuiApp PRIVATE Qt${QT_VERSION_MAJOR}::Sql)
target_link_libraries(GuiApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libsodium-win64/lib/libsodium.a)



set_target_properties(GuiApp PROPERTIES
    ${BUNDLE_ID_OPTION}
    WIN64_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS GuiApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/icon.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GuiApp)
endif()
