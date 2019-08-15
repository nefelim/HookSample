set(SRC
    DetoursHook.cpp
    DetoursProcessor.cpp
    pch.cpp
    )

file(GLOB_RECURSE HEADERS "*.h")

source_group(TREE ${CMAKE_SOURCE_DIR}/DetoursHook FILES ${SRC})
source_group(TREE ${CMAKE_SOURCE_DIR}/DetoursHook FILES ${HEADERS})

add_library(DetoursHook SHARED ${SRC} ${HEADERS})

set_target_properties(DetoursHook PROPERTIES COMPILE_FLAGS "/Yupch.h")
set_source_files_properties(pch.cpp PROPERTIES COMPILE_FLAGS "/Ycpch.h")

target_link_libraries(DetoursHook PRIVATE detours_static plog::plog exceptxx)
TARGET_COMPILE_DEFINITIONS(DetoursHook PUBLIC ${DETOURS_COMPILE_DEFINITIONS})
TARGET_COMPILE_OPTIONS(DetoursHook PUBLIC ${DETOURS_COMPILE_OPTIONS})
target_include_directories(DetoursHook 
    INTERFACE 
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)