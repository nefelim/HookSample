set(SRC
    benchmark.cpp
    pch.cpp
    )

file(GLOB_RECURSE HEADERS "*.h")

source_group(TREE ${CMAKE_SOURCE_DIR}/Benchmark FILES ${SRC})
source_group(TREE ${CMAKE_SOURCE_DIR}/Benchmark FILES ${HEADERS})

add_executable(Benchmark ${SRC} ${HEADERS})

set_target_properties(Benchmark PROPERTIES COMPILE_FLAGS "/Yupch.h")
set_source_files_properties(pch.cpp PROPERTIES COMPILE_FLAGS "/Ycpch.h")

target_link_libraries(Benchmark PRIVATE plog::plog exceptxx Common)