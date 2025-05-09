function(generate_qml_qrc)
    set(options)
    set(oneValueArgs TARGET_NAME QML_DIR RESOURCES_DIR OUTPUT_QRC QML_PREFIX RESOURCES_PREFIX)
    set(multiValueArgs)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Set qrc prefix by default
    if(NOT ARG_QML_PREFIX)
        set(ARG_QML_PREFIX "/ui")
    endif()

    if(NOT ARG_RESOURCES_PREFIX)
        set(ARG_RESOURCES_PREFIX "/icons")
    endif()

    file(GLOB_RECURSE QML_FILES "${ARG_QML_DIR}/*.qml" "${ARG_QML_DIR}/qmldir")

    file(GLOB_RECURSE ICONS "${ARG_RESOURCES_DIR}/*.svg" "${ARG_QML_DIR}/*.png")
    file(GLOB_RECURSE FONTS "${ARG_RESOURCES_DIR}/*.ttf" "${ARG_RESOURCES_DIR}/*.otf")

    set(RESOURCES_LIST)
    list(APPEND RESOURCES_LIST ${ICONS})
    list(APPEND RESOURCES_LIST ${FONTS})

#==============================ADD QML==========================================
    set(QRC_CONTENT "<RCC>\n  <qresource prefix=\"${ARG_QML_PREFIX}\">\n")

    foreach(QML_FILE ${QML_FILES})
        # Get relative path
        file(RELATIVE_PATH REL_PATH ${ARG_QML_DIR} ${QML_FILE})

        if( "${REL_PATH}" STREQUAL ""  )
            message("Can't generate relative path")
        endif ()

        set(QRC_CONTENT "${QRC_CONTENT}    <file alias=\"${REL_PATH}\">${QML_FILE}</file>\n")

    endforeach()
    set(QRC_CONTENT "${QRC_CONTENT}  </qresource>\n\n")

#==============================ADD RESOURCES==========================================
    set(QRC_CONTENT "${QRC_CONTENT}  <qresource prefix=\"${ARG_RESOURCES_PREFIX}\">\n")
    foreach(RESOURCE ${RESOURCES_LIST})
        # Get relative path
        file(RELATIVE_PATH REL_PATH ${ARG_RESOURCES_DIR} ${RESOURCE})

        if( "${REL_PATH}" STREQUAL ""  )
            message("Can't generate relative path")
        endif ()

        set(QRC_CONTENT "${QRC_CONTENT}    <file alias=\"${REL_PATH}\">${RESOURCE}</file>\n")
    endforeach()
    set(QRC_CONTENT "${QRC_CONTENT}  </qresource>\n")

    set(QRC_CONTENT "${QRC_CONTENT}</RCC>")

    file(WRITE ${ARG_OUTPUT_QRC} ${QRC_CONTENT})

    if(TARGET ${ARG_TARGET_NAME}) #if target initialized
        qt_add_resources(RESOURCE_FILE ${ARG_OUTPUT_QRC})
        target_sources(${ARG_TARGET_NAME} PRIVATE ${RESOURCE_FILE})
    else()
        message(WARNING "Target ${ARG_TARGET_NAME} not found for QRC generation")
    endif()
endfunction()