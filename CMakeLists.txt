add_library(datalink src/datalink.c)

target_include_directories(datalink PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)