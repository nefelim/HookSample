add_subdirectory(Detours EXCLUDE_FROM_ALL)
target_include_directories(detours_static INTERFACE Detours/src)

add_subdirectory(plog)

add_library(exceptxx INTERFACE)
target_include_directories(exceptxx INTERFACE exceptxx/include)

add_subdirectory(mhook EXCLUDE_FROM_ALL)
target_include_directories(mhook INTERFACE mhook/mhook-lib)