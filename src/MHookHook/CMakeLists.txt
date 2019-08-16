set(SRC
    MHookHook.cpp
    MHookProcessor.cpp
    pch.cpp
    )

file(GLOB_RECURSE HEADERS "*.h")

source_group(TREE ${CMAKE_SOURCE_DIR}/MHookHook FILES ${SRC})
source_group(TREE ${CMAKE_SOURCE_DIR}/MHookHook FILES ${HEADERS})

add_library(MHookHook SHARED ${SRC} ${HEADERS})

set_target_properties(MHookHook PROPERTIES COMPILE_FLAGS "/Yupch.h")
set_source_files_properties(pch.cpp PROPERTIES COMPILE_FLAGS "/Ycpch.h")

target_link_libraries(MHookHook PRIVATE mhook plog::plog exceptxx)