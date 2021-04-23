#include "catch.hpp"

#include "particleparam.h"

TEST_CASE( "Test ParticleParam", "[ParticleParam]") {
  // Build Event.
  Event ev;
  // Add particle to event.
  ev.particles().push_back( Particle() );

  // Add PID.
  ev.particle(0).pid() = 421;

  // Add charge.
  ev.particle(0).charge() = +1;

  // Add time.
  ev.particle(0).time() = 0.5;

  // Set momentum of particle.
  FourVector v1(1,1,1,1);
  ev.particle(0).SetMomentum( v1 );

  SECTION("Test PID") {
    Param* param = new ParticleParam<Param::PID>("PID","pid",0);
    param->operator()(ev);
    REQUIRE( ev["PID"] == 421 );
  }

  SECTION("Test Q") {
    Param* param = new ParticleParam<Param::Q>("q","q",0);
    param->operator()(ev);
    REQUIRE( ev["q"] == +1 );
  }

  SECTION("Test T") {
    Param* param = new ParticleParam<Param::T>("t","t",0);
    param->operator()(ev);
    REQUIRE( ev["t"] == 0.5 );
  }

  SECTION("Test M") {
    Param* param = new ParticleParam<Param::M>("Mass","M",0);
    param->operator()(ev);
    REQUIRE( ev["Mass"] == v1.M() );
  }

  SECTION("Test MSq") {
    Param* param = new ParticleParam<Param::MSq>("MassSq","MSq",0);
    param->operator()(ev);
    REQUIRE( ev["MassSq"] == v1.M2() );
  }

  SECTION("Test Px") {
    Param* param = new ParticleParam<Param::PX>("Px","Px",0);
    param->operator()(ev);
    REQUIRE( ev["Px"] == v1.Px() );
  }

  SECTION("Test Py") {
    Param* param = new ParticleParam<Param::PY>("Py","Py",0);
    param->operator()(ev);
    REQUIRE( ev["Py"] == v1.Py() );
  }

  SECTION("Test Pz") {
    Param* param = new ParticleParam<Param::PZ>("Pz","Pz",0);
    param->operator()(ev);
    REQUIRE( ev["Pz"] == v1.Pz() );
  }

  SECTION("Test Pt") {
    Param* param = new ParticleParam<Param::PT>("Pt","Pt",0);
    param->operator()(ev);
    REQUIRE( ev["Pt"] == v1.Pt() );
  }

  SECTION("Test P") {
    Param* param = new ParticleParam<Param::P>("P","P",0);
    param->operator()(ev);
    REQUIRE( ev["P"] == v1.P() );
  }

  SECTION("Test E") {
    Param* param = new ParticleParam<Param::E>("E","E",0);
    param->operator()(ev);
    REQUIRE( ev["E"] == v1.E() );
  }
}