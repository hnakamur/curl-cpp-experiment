include(FetchContent)
fetchcontent_declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG main
)
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE
)
fetchcontent_makeavailable(googletest)

set(TEST_FILENAMES sample1_unittest.cc)
list(TRANSFORM TEST_FILENAMES PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/ OUTPUT_VARIABLE TEST_FILES)

add_executable(sample1_unittest ${TEST_FILES})
target_link_libraries(sample1_unittest PRIVATE sample1 GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(sample1_unittest)
