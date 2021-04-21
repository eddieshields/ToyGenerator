#include "catch.hpp"

#include "descriptor.h"

TEST_CASE( "Test descriptor", "[Descriptor]") {

  SECTION("Check print and size") {
    DecayDescriptor descriptor;
    descriptor("D0 => K_S0 K+ K-");
    REQUIRE( descriptor.getParticles().size() == 4 );
  }

  SECTION("Check charges") {
    DecayDescriptor descriptor;
    descriptor("D0 => K_S0 K+ K-");
    REQUIRE( descriptor.getCharges()[0] == 0 );
    REQUIRE( descriptor.getCharges()[1] == 0 );
    REQUIRE( descriptor.getCharges()[2] == +1 );
    REQUIRE( descriptor.getCharges()[3] == -1 );
  }
}