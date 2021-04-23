#include "catch.hpp"

#include "random.h"

TEST_CASE( "Test Random number generator", "[Random]" ) {
  //SECTION("Check Rnd") {
  //  REQUIRE( 0 < Random::Rnd() < 1 );
  //}

  SECTION("Check flat") {
    REQUIRE( Random::flat(5,10) < 10 );
    REQUIRE( Random::flat(5,10) > 5  );
  }

  //SECTION("Check uniform") {
  //  REQUIRE( 1 < Random::uniform() < 1 );
  //}

  SECTION("Check exponential") {
    REQUIRE( Random::exponential() > 0 );
  }

  //SECTION("Check integer") {
  //  REQUIRE( Random::integer() == 1 || Random::integer() == 0 );
  //}

  //SECTION("Check bool") {
  //  REQUIRE( Random::Bool() == true || Random::Bool() == false );
  //}
}