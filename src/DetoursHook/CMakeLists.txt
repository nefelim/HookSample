set(SRC
    DetoursHook.cpp
    pch.cpp
    )

file(GLOB_RECURSE HEADERS "*.h")

source_group(TREE ${CMAKE_SOURCE_DIR}/DetoursHook FILES ${SRC})
source_group(TREE ${CMAKE_SOURCE_DIR}/DetoursHook FILES ${HEADERS})

add_executable(DetoursHook ${SRC} ${HEADERS})
target_link_libraries(DetoursHook)

set_target_properties(DetoursHook PROPERTIES COMPILE_FLAGS "/Yupch.h")
set_source_files_properties(pch.cpp PROPERTIES COMPILE_FLAGS "/Ycpch.h")

target_link_libraries(DetoursHook PRIVATE detours_static)
TARGET_COMPILE_DEFINITIONS(DetoursHook PUBLIC ${DETOURS_COMPILE_DEFINITIONS})
TARGET_COMPILE_OPTIONS(DetoursHook PUBLIC ${DETOURS_COMPILE_OPTIONS})