cmake_minimum_required(VERSION 3.16)

project(GuiApp VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Sql)

set(DIR_MAIN ${CMAKE_CURRENT_SOURCE_DIR})
set(DIR_CHACHA20 chacha20)
set(DIR_CRYPTO crypto)
set(DIR_DATABASE database)

add_subdirectory(${DIR_CHACHA20})

set(SOURCES_CRYPTO
    ${DIR_CRYPTO}/crypto.h
    ${DIR_CRYPTO}/crypto.cpp
    ${DIR_CRYPTO}/keystream.cpp
)

set(SOURCES_DATABASE
    ${DIR_DATABASE}/database.h
    ${DIR_DATABASE}/database.cpp
    ${DIR_DATABASE}/database_structure.cpp
)

set(SOURCES_PROJECT
    main.cpp
    ${SOURCES_CRYPTO}
    ${SOURCES_DATABASE}
    utils.h
    widget.cpp
    widget.h
)

qt_add_executable(GuiApp MANUAL_FINALIZATION ${SOURCES_PROJECT})

target_include_directories(GuiApp PRIVATE ${DIR_MAIN})
target_include_directories(GuiApp PRIVATE ${DIR_CRYPTO})
target_include_directories(GuiApp PRIVATE ${DIR_DATABASE})

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
