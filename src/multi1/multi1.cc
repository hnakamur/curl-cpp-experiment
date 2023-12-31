#include <iostream>
#include <ostream>

#include <argparse/argparse.hpp>
#include <curlcpp/curl_easy.h>
#include <curlcpp/curl_multi.h>
#include <curlcpp/curl_ios.h>

using curl::curl_easy;
using curl::curl_multi;
using curl::curl_ios;
using curl::curl_easy_exception;
using curl::curlcpp_traceback;

/**
 * This example shows how to make multiple requests
 * using curl_multi interface.
 */
int
main(int argc, char *argv[])
{
  argparse::ArgumentParser program("multi1");
  program.add_argument("-u", "--url").required().help("target URL");
  program.add_argument("-c", "--concurrency").required().help("concurrent client count").scan<'i', int>();
  ;
  try {
    program.parse_args(argc, argv);
  } catch (const std::exception &err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    return 2;
  }
  std::string url = program.get<std::string>("--url");
  int concurrency = program.get<int>("--concurrency");
  std::cout << "URL: " << url << ", CONCURRENCY: " << concurrency << std::endl;

  // Create a vector of curl easy handlers.
  std::vector<curl_easy> handlers;

  // Create a vector of curl streams.
  std::vector<curl_ios<std::ostringstream>> streams;

  // Create the curl easy handler and associated the streams with it.
  for (int i = 0; i < concurrency; ++i) {
    auto *output_stream = new std::ostringstream;
    curl_ios<std::ostringstream> curl_stream(*output_stream);

    curl_easy easy(curl_stream);
    easy.add<CURLOPT_URL>(url.c_str());
    easy.add<CURLOPT_FOLLOWLOCATION>(1L);

    streams.emplace_back(curl_stream);
    handlers.emplace_back(easy);
  }

  // Create a map of curl pointers to output streams.
  std::unordered_map<CURL *, curl_ios<std::ostringstream> *> easy_streams;
  for (int i = 0; i < handlers.size(); ++i) {
    easy_streams[handlers.at(i).get_curl()] = (curl_ios<std::ostringstream> *)&streams.at(i);
  }

  // Add all the handlers to the curl multi object.
  curl_multi multi;
  multi.add(handlers);

  try {
    // Start the transfers.
    multi.perform();

    // Until there are active transfers, call the perform() API.
    while (multi.get_active_transfers()) {
      multi.perform();

      // Extracts the first finished request.
      std::unique_ptr<curl_multi::curl_message> message = multi.get_next_finished();
      if (message != nullptr) {
        const curl_easy *handler = message->get_handler();

        // Get the stream associated with the curl easy handler.
        curl_ios<std::ostringstream> stream_handler = *easy_streams[handler->get_curl()];

        auto content       = stream_handler.get_stream()->str();
        auto url           = handler->get_info<CURLINFO_EFFECTIVE_URL>();
        auto response_code = handler->get_info<CURLINFO_RESPONSE_CODE>();
        auto content_type  = handler->get_info<CURLINFO_CONTENT_TYPE>();
        auto http_code     = handler->get_info<CURLINFO_HTTP_CODE>();

        std::cout << "CODE: " << response_code.get() << ", TYPE: " << content_type.get() << ", HTTP_CODE: " << http_code.get()
                  << ", URL: " << url.get() << ", CONTENT: " << content.substr(0, 10) + " ... " << std::endl;
      }
    }

    // Free the memory allocated for easy streams.
    for (auto stream : streams) {
      delete stream.get_stream();
    }

  } catch (curl_easy_exception &error) {
    // If you want to print the last error.
    std::cerr << error.what() << std::endl;
  }
  return 0;
}
