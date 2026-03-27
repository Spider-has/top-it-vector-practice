#ifndef PRETTY_OUTPUT_HPP
#define PRETTY_OUTPUT_HPP

#include <iostream>

#include "Test.hpp"

namespace prettyOut
{
  static constexpr char BOLD_TEXT[] = "\033[1m";
  static constexpr char GREEN_TEXT[] = "\033[32m";
  static constexpr char RED_TEXT[] = "\033[31m";
  static constexpr char CLEAR_STYLE[] = "\033[0m";

  void printFailedTestInfo(const Test::Test &test, size_t i)
  {
    std::cout << RED_TEXT << i << ". [-] " << test.desc << ": " << BOLD_TEXT << __FILE_NAME__ << ":" << test.line << "-"
              << test.func_name << CLEAR_STYLE << "\n";
  }

  void printRunTests()
  {
    std::cout << "Run tests in file: " << BOLD_TEXT << __FILE_NAME__ << CLEAR_STYLE << "\n\n";
  }

  void printAllTestsSuccessed(size_t count)
  {
    std::cout << GREEN_TEXT << "All tests passed successfully: " << BOLD_TEXT << count << " / " << count << "\n"
              << CLEAR_STYLE;
  }

  void someTestsFailed(size_t success, size_t count)
  {
    std::cout << "Some test " << RED_TEXT << "failed with errors: " << CLEAR_STYLE << BOLD_TEXT << success << " / "
              << count << "\n"
              << CLEAR_STYLE;
  }

  void printSuccessedBeforeTests(size_t left_success, size_t right_success)
  {
    std::cout << GREEN_TEXT << left_success << "-" << right_success << ". [+]" << CLEAR_STYLE << "\n";
  }
}

#endif
