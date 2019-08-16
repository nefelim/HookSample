set(SRC
    DetoursInject.cpp
    pch.cpp
    )

file(GLOB_RECURSE HEADERS "*.h")

source_group(TREE ${CMAKE_SOURCE_DIR}/DetoursInject FILES ${SRC})
source_group(TREE ${CMAKE_SOURCE_DIR}/DetoursInject FILES ${HEADERS})

add_library(DetoursInject STATIC ${SRC} ${HEADERS})

set_target_properties(DetoursInject PROPERTIES COMPILE_FLAGS "/Yupch.h")
set_source_files_properties(pch.cpp PROPERTIES COMPILE_FLAGS "/Ycpch.h")

target_link_libraries(DetoursInject PRIVATE detours_static)
target_include_directories(DetoursInject 
    INTERFACE 
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)