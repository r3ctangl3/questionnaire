qt_add_library( DurkaQml STATIC )

set_target_properties( DurkaQml PROPERTIES AUTOMOC ON )

target_link_libraries( DurkaQml PRIVATE
        Qt6::Core
        Qt6::Quick
        Qt6::Qml
)

list( APPEND QML_FILES
        main.qml
        custom/MyRectangle.qml
)

qt6_add_qml_module( DurkaQml
        URI Durka
        VERSION 1.0
        RESOURCE_PREFIX /Durka
        QML_FILES
            ${QML_FILES}
        RESOURCES
            custom/qmldir
        OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/qml
)



install(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
        DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/qml
        FILES_MATCHING PATTERN "*qml" PATTERN "qmldir"
)