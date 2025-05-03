function(generate_qml_qrc)
    set(options)
    set(oneValueArgs TARGET_NAME QML_DIR OUTPUT_QRC PREFIX)
    set(multiValueArgs)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Set qrc prefix by default
    if(NOT ARG_PREFIX)
        set(ARG_PREFIX "/")
    endif()

    file(GLOB_RECURSE QML_FILES "${ARG_QML_DIR}/*.qml" "${ARG_QML_DIR}/qmldir")

    set(QRC_CONTENT "<RCC>\n  <qresource prefix=\"${ARG_PREFIX}\">\n")

    foreach(QML_FILE ${QML_FILES})
        # Get relative path
        file(RELATIVE_PATH REL_PATH ${ARG_QML_DIR} ${QML_FILE})

        if( "${REL_PATH}" STREQUAL ""  )
            message("Can't generate relative path")
        endif ()


        set(QRC_CONTENT "${QRC_CONTENT}    <file alias=\"${REL_PATH}\">${QML_FILE}</file>\n")
    endforeach()

    set(QRC_CONTENT "${QRC_CONTENT}  </qresource>\n</RCC>")

    file(WRITE ${ARG_OUTPUT_QRC} ${QRC_CONTENT})

    if(TARGET ${ARG_TARGET_NAME}) #if target initialized
        qt_add_resources(RESOURCE_FILE ${ARG_OUTPUT_QRC})
        target_sources(${ARG_TARGET_NAME} PRIVATE ${RESOURCE_FILE})
    else()
        message(WARNING "Target ${ARG_TARGET_NAME} not found for QRC generation")
    endif()
endfunction()