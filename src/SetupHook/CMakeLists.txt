set(SRC
    SetupHook.cpp
    pch.cpp
    )

file(GLOB_RECURSE HEADERS "*.h")

source_group(TREE ${CMAKE_SOURCE_DIR}/SetupHook FILES ${SRC})
source_group(TREE ${CMAKE_SOURCE_DIR}/SetupHook FILES ${HEADERS})

add_executable(SetupHook ${SRC} ${HEADERS})
target_link_libraries(SetupHook PRIVATE DetoursInject exceptxx)

set_target_properties(SetupHook PROPERTIES COMPILE_FLAGS "/Yupch.h")
set_source_files_properties(pch.cpp PROPERTIES COMPILE_FLAGS "/Ycpch.h")