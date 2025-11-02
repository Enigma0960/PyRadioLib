#
#   TARGET <name>
#   ROOT_DIR <path>
#   DEST_DIR <path>
#   FILES <NAME>
function(copy_headers TARGET ROOT_DIR DEST_DIR)
    set(FILES ${ARGN})

    if (NOT FILES)
        message(STATUS "copy_headers(${TARGET}): список файлов пуст — таргет будет пустым")
        add_custom_target(${TARGET})
        return()
    endif ()


    set(COPY_SCRIPT "${CMAKE_BINARY_DIR}/${TARGET}_copy_headers.cmake")
    file(WRITE "${COPY_SCRIPT}" "file(MAKE_DIRECTORY \"${DEST_DIR}\")\n")

    set(OUTPUTS)
    foreach (src IN LISTS FILES)
        if (NOT EXISTS "${src}")
            message(FATAL_ERROR "copy_headers(${TARGET}): файл '${src}' не существует")
        endif ()

        # получаем путь относительно ROOT_DIR
        file(RELATIVE_PATH rel "${ROOT_DIR}" "${src}")

        if (rel MATCHES "^[.][.]/")
            message(FATAL_ERROR
                    "copy_headers(${TARGET}): файл '${src}' находится вне ROOT_DIR='${ROOT_DIR}'")
        endif ()

        # итоговый путь в выходной директории
        set(dst "${DEST_DIR}/${rel}")
        get_filename_component(dst_dir "${dst}" DIRECTORY)

        # генерируем в скрипт mkdir + copy_if_different
        file(APPEND "${COPY_SCRIPT}" "file(MAKE_DIRECTORY \"${dst_dir}\")\n")
        file(APPEND "${COPY_SCRIPT}"
                "execute_process(COMMAND \"${CMAKE_COMMAND}\" -E copy_if_different \"${src}\" \"${dst}\")\n")

        list(APPEND OUTPUTS "${dst}")
    endforeach ()

    add_custom_command(
            OUTPUT ${OUTPUTS}
            COMMAND ${CMAKE_COMMAND} -P "${COPY_SCRIPT}"
            DEPENDS ${FILES}
            COMMENT "Copy headers for ${TARGET} from ${ROOT_DIR} to ${DEST_DIR}"
            VERBATIM
    )

    add_custom_target(${TARGET} DEPENDS ${OUTPUTS})

endfunction()