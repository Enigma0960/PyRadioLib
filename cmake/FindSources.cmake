


function(collect_sources TARGET_DIR OUT_CPP_VAR OUT_H_VAR)
    if (NOT IS_DIRECTORY "${TARGET_DIR}")
        message(FATAL_ERROR "collect_sources: путь не существует или не является директорией: ${TARGET_DIR}")
    endif ()

    file(GLOB_RECURSE CPP_LIST CONFIGURE_DEPENDS
            "${TARGET_DIR}/*.cpp"
            "${TARGET_DIR}/*.cxx"
            "${TARGET_DIR}/*.cc"
    )

    file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS
            "${TARGET_DIR}/*.h"
            "${TARGET_DIR}/*.hpp"
            "${TARGET_DIR}/*.hh"
    )

    set(${OUT_CPP_VAR} ${CPP_LIST} PARENT_SCOPE)
    set(${OUT_H_VAR} ${HEADER_LIST} PARENT_SCOPE)
endfunction()