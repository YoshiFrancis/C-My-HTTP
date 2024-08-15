#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>

TEST_CASE( "Default", "[TEST]" ) {
  std::cout << "TESTING\n";
     SECTION( "ABLE TO TEST ") {
      REQUIRE(1 == 1);
     }
}