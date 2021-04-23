#include "catch.hpp"

#include "eventparam.h"

TEST_CASE( "Test EventParam", "[EventParam]") {
  // Build Event.
  Event ev;
  
  // Add pdf information.
  ev.pdf = 0.9;

  // Add weight information.
  ev.weight = 0.5;

  SECTION("Test PDF") {
    Param* param = new EventParam<Param::PDF>("PDF","pdf");
    param->operator()(ev);
    REQUIRE( ev["PDF"] == 0.9f );
  }

  SECTION("Test weight") {
    Param* param = new EventParam<Param::W>("weight","w");
    param->operator()(ev);
    REQUIRE( ev["weight"] == 0.5 );
  }

}