set(SRC
    HelloWorld.cpp
    pch.cpp
    )

file(GLOB_RECURSE HEADERS "*.h")

source_group(TREE ${CMAKE_SOURCE_DIR}/HelloWorld FILES ${SRC})
source_group(TREE ${CMAKE_SOURCE_DIR}/HelloWorld FILES ${HEADERS})

add_executable(HelloWorld ${SRC} ${HEADERS})
target_link_libraries(HelloWorld)

set_target_properties(HelloWorld PROPERTIES COMPILE_FLAGS "/Yupch.h")
set_source_files_properties(pch.cpp PROPERTIES COMPILE_FLAGS "/Ycpch.h")