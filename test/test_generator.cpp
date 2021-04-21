#include "catch.hpp"

#include "generator.h"
#include "descriptor.h"
#include "event.h"

TEST_CASE( "Generator will generate events", "[Generator]") {
  // Set Decay.
  gDescriptor("D0 => K_S0 K+ K-");
  // Create Generator.
  Generator gen("Generator");

  SECTION("Generate decay") {
    // Define event.
    Event ev;
    // Generate event.
    gen(ev);
    REQUIRE( ev.mother().time() > 0 );
    REQUIRE( ev.particles().size() == 4 );
  }
}