
#include "curlcpp/curl_easy.h"
#include "curlcpp/curl_ios.h"
#include "curlcpp/curl_exception.h"

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
  std::ostringstream header_stream;
  std::ostringstream body_stream;

  curl::curl_ios<std::ostringstream> header_ios(header_stream);
  curl::curl_ios<std::ostringstream> body_ios(body_stream);

  curl::curl_easy easy;

  easy.add<CURLOPT_WRITEFUNCTION>(header_ios.get_function());
  easy.add<CURLOPT_HEADERDATA>(header_ios.get_stream());

  easy.add<CURLOPT_WRITEDATA>(body_ios.get_stream());

  easy.add<CURLOPT_URL>("http://localhost");
  easy.add<CURLOPT_FOLLOWLOCATION>(1L);

  try {
    easy.perform();

    auto x = easy.get_info<CURLINFO_CONTENT_TYPE>();
    std::cout << "just content-type: " << x.get() << std::endl;

    std::cout << "--- header ---\n" << header_stream.str() << std::endl;
    std::cout << "--- body ---\n" << body_stream.str() << std::endl;
  } catch (curl::curl_easy_exception &error) {
    // If you want to print the last error.
    std::cerr << error.what() << std::endl;

    // If you want to print the entire error stack you can do
    error.print_traceback();
  }
  return 0;
}
