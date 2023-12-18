
#include "curlcpp/curl_easy.h"

using curl::curl_easy;
using curl::curl_easy_exception;
using curl::curlcpp_traceback;

#include "sample1.h"

int
Factorial(int n)
{
  int result = 1;
  for (int i = 1; i <= n; i++) {
    result *= i;
  }

  return result;
}

/**
 * This example shows how to make a simple request with curl.
 */
int
main()
{
  // Easy object to handle the connection.
  curl_easy easy;

  // Add some options.
  easy.add<CURLOPT_URL>("http://localhost");
  easy.add<CURLOPT_FOLLOWLOCATION>(1L);

  try {
    easy.perform();
  } catch (curl_easy_exception &error) {
    // If you want to print the last error.
    std::cerr << error.what() << std::endl;
  }
  return 0;
}
