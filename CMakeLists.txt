if (NOT TARGET keypad_matrix)
    add_library(keypad_matrix INTERFACE)

    target_sources(keypad_matrix INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/keypad.c
    )

    target_include_directories(keypad_matrix INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}
    )

    target_link_libraries(keypad_matrix INTERFACE
        pico_stdlib
    )
endif()