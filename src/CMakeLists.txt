include(curlcpp)

include(CMakePrintHelpers)
cmake_print_properties(TARGETS curlcpp PROPERTIES TYPE SOURCE_DIR)
cmake_print_properties(TARGETS curlcpp PROPERTIES INTERFACE_INCLUDE_DIRECTORIES)
cmake_print_properties(TARGETS curlcpp PROPERTIES PUBLIC_HEADER)

set(SRC_FILENAMES sample1.cc)
list(TRANSFORM SRC_FILENAMES PREPEND ${PROJECT_SOURCE_DIR}/src/ OUTPUT_VARIABLE SRC_FILES)

add_executable(sample1 ${SRC_FILES})
target_include_directories(sample1 PRIVATE . ${curlcpp_SOURCE_DIR})
target_link_libraries(sample1 PRIVATE curlcpp)
install(TARGETS sample1)
