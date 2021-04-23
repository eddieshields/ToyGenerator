#include "catch.hpp"

#include "compositeparam.h"

TEST_CASE( "Test CompositeParam", "[CompositeParam]") {
  // Build Event.
  Event ev;
  // Add two particles to event.
  ev.particles().push_back( Particle() );
  ev.particles().push_back( Particle() );

  // Add charge.
  ev.particle(0).charge() = +1;
  ev.particle(1).charge() = -1;

  // Set momentum of particles.
  FourVector v1(1,1,1,1);
  ev.particle(0).SetMomentum( v1 );
  FourVector v2(2,2,2,2);
  ev.particle(1).SetMomentum( v2 );

  SECTION("Test M") {
    Param* param = new CompositeParam<Param::M>("Mass","M",0,1);
    param->operator()(ev);
    REQUIRE( ev["Mass"] == (v1 + v2).M() );
  }

  SECTION("Test MSq") {
    Param* param = new CompositeParam<Param::MSq>("MassSq","MSq",0,1);
    param->operator()(ev);
    REQUIRE( ev["MassSq"] == (v1 + v2).M2() );
  }

  SECTION("Test Px") {
    Param* param = new CompositeParam<Param::PX>("Px","Px",0,1);
    param->operator()(ev);
    REQUIRE( ev["Px"] == (v1 + v2).Px() );
  }

  SECTION("Test Py") {
    Param* param = new CompositeParam<Param::PY>("Py","Py",0,1);
    param->operator()(ev);
    REQUIRE( ev["Py"] == (v1 + v2).Py() );
  }

  SECTION("Test Pz") {
    Param* param = new CompositeParam<Param::PZ>("Pz","Pz",0,1);
    param->operator()(ev);
    REQUIRE( ev["Pz"] == (v1 + v2).Pz() );
  }

  SECTION("Test Pt") {
    Param* param = new CompositeParam<Param::PT>("Pt","Pt",0,1);
    param->operator()(ev);
    REQUIRE( ev["Pt"] == (v1 + v2).Pt() );
  }

  SECTION("Test P") {
    Param* param = new CompositeParam<Param::P>("P","P",0,1);
    param->operator()(ev);
    REQUIRE( ev["P"] == (v1 + v2).P() );
  }

  SECTION("Test E") {
    Param* param = new CompositeParam<Param::E>("E","E",0,1);
    param->operator()(ev);
    REQUIRE( ev["E"] == (v1 + v2).E() );
  }
}