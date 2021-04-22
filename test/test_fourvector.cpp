#include "catch.hpp"

#include "fourvector.h"

#include <cmath>

TEST_CASE( "Test FourVector", "[FourVector]" ) {
  FourVector v1(1,1,1,1);
  FourVector v2(2,2,2,2);

  SECTION("Add two vectors") {
    FourVector v3 = v1 + v2;
    REQUIRE( v3.X()  == 3 );
    REQUIRE( v3.Y()  == 3 );
    REQUIRE( v3.Z()  == 3 );
    REQUIRE( v3.T()  == 3 );
    REQUIRE( v3.Px() == 3 );
    REQUIRE( v3.Py() == 3 );
    REQUIRE( v3.Pz() == 3 );
    REQUIRE( v3.E()  == 3 );
  }

  SECTION("Subtract two vectors") {
    FourVector v4 = v2 - v1;
    REQUIRE( v4.X()  == 1 );
    REQUIRE( v4.Y()  == 1 );
    REQUIRE( v4.Z()  == 1 );
    REQUIRE( v4.T()  == 1 );
    REQUIRE( v4.Px() == 1 );
    REQUIRE( v4.Py() == 1 );
    REQUIRE( v4.Pz() == 1 );
    REQUIRE( v4.E()  == 1 );
  }

  SECTION("Multiply two vectors") {
    real_t v5 = v1 * v2;
    REQUIRE( v5 == 8 );
  }

  SECTION("Add to vector") {
    FourVector v6(3,3,3,3);
    v6 += v1;
    REQUIRE( v6.X()  == 4 );
    REQUIRE( v6.Y()  == 4 );
    REQUIRE( v6.Z()  == 4 );
    REQUIRE( v6.T()  == 4 );
    REQUIRE( v6.Px() == 4 );
    REQUIRE( v6.Py() == 4 );
    REQUIRE( v6.Pz() == 4 );
    REQUIRE( v6.E()  == 4 );
  }

  SECTION("Check methods") {
    FourVector v7(1,2,3,4);
    REQUIRE( v7.P()    == (real_t)std::sqrt(14) );
    REQUIRE( v7.Pt()   == (real_t)std::sqrt(5)  );
    REQUIRE( v7.M()    == 2  );
    REQUIRE( v7.M2()   == 4  );
    REQUIRE( v7.Mag()  == 2  );
    REQUIRE( v7.Mag2() == 4  );
  }

  SECTION("Check setters") {
    FourVector v8(1,1,1,1);
    v8.SetXYZT(2,2,2,2);
    REQUIRE( v8.X()  == 2 );
    REQUIRE( v8.Y()  == 2 );
    REQUIRE( v8.Z()  == 2 );
    REQUIRE( v8.T()  == 2 );
    REQUIRE( v8.Px() == 2 );
    REQUIRE( v8.Py() == 2 );
    REQUIRE( v8.Pz() == 2 );
    REQUIRE( v8.E()  == 2 );

    v8.SetPxPyPzE(3,3,3,3);
    REQUIRE( v8.X()  == 3 );
    REQUIRE( v8.Y()  == 3 );
    REQUIRE( v8.Z()  == 3 );
    REQUIRE( v8.T()  == 3 );
    REQUIRE( v8.Px() == 3 );
    REQUIRE( v8.Py() == 3 );
    REQUIRE( v8.Pz() == 3 );
    REQUIRE( v8.E()  == 3 );
  }

  SECTION("Check indices") {
    REQUIRE( v1[0] == 1 );
    REQUIRE( v1[1] == 1 );
    REQUIRE( v1[2] == 1 );
    REQUIRE( v1[3] == 1 );
    REQUIRE( v1(0) == 1 );
    REQUIRE( v1(1) == 1 );
    REQUIRE( v1(2) == 1 );
    REQUIRE( v1(3) == 1 );
  }
}