include(FetchContent)
fetchcontent_declare(
  argparse
  GIT_REPOSITORY https://github.com/p-ranav/argparse.git
  GIT_TAG master
)
fetchcontent_makeavailable(argparse)
