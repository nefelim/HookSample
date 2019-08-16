set(SRC
    SetupDetoursHook.cpp
    pch.cpp
    )

file(GLOB_RECURSE HEADERS "*.h")

source_group(TREE ${CMAKE_SOURCE_DIR}/SetupDetoursHook FILES ${SRC})
source_group(TREE ${CMAKE_SOURCE_DIR}/SetupDetoursHook FILES ${HEADERS})

add_executable(SetupDetoursHook ${SRC} ${HEADERS})
target_link_libraries(SetupDetoursHook PRIVATE DetoursInject)

set_target_properties(SetupDetoursHook PROPERTIES COMPILE_FLAGS "/Yupch.h")
set_source_files_properties(pch.cpp PROPERTIES COMPILE_FLAGS "/Ycpch.h")