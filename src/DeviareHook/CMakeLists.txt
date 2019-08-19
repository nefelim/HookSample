set(SRC
    DeviareHook.cpp
    DeviareProcessor.cpp
    pch.cpp
    )

file(GLOB_RECURSE HEADERS "*.h")

source_group(TREE ${CMAKE_SOURCE_DIR}/DeviareHook FILES ${SRC})
source_group(TREE ${CMAKE_SOURCE_DIR}/DeviareHook FILES ${HEADERS})

add_library(DeviareHook SHARED ${SRC} ${HEADERS})

set_target_properties(DeviareHook PROPERTIES COMPILE_FLAGS "/Yupch.h")
set_source_files_properties(pch.cpp PROPERTIES COMPILE_FLAGS "/Ycpch.h")

target_link_libraries(DeviareHook PRIVATE plog::plog exceptxx)