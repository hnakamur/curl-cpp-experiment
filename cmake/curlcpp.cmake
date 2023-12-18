include(FetchContent)
fetchcontent_declare(
  curlcpp
  GIT_REPOSITORY https://github.com/JosephP91/curlcpp.git
  GIT_TAG master
)
fetchcontent_makeavailable(curlcpp)

# NOTE: Use the following directive to include curlcpp header files:
# #include "curlcpp/curl_easy.h"
#
# Add following settings for your target:
#
# target_include_directories(your_target PRIVATE . ${curlcpp_SOURCE_DIR})
# target_link_libraries(your_target PRIVATE curlcpp)
#
# The following symlink is needed to make it possible to include head files
# with #include "curlcpp/curl_easy.h".
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink include ${curlcpp_SOURCE_DIR}/curlcpp)
