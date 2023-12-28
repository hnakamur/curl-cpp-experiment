include(curlcpp)

function(add_example target src_filenames)
  list(TRANSFORM src_filenames PREPEND ${PROJECT_SOURCE_DIR}/src/${target}/ OUTPUT_VARIABLE src_files)
  add_executable(${target} ${src_files})
  target_include_directories(${target} PRIVATE . ${curlcpp_SOURCE_DIR})
  target_link_libraries(${target} PRIVATE curlcpp)
  install(TARGETS ${target})
endfunction()

add_example(easy1 easy1.cc)
add_example(multi1 multi1.cc)
