// test_main.cpp : Defines the entry point for the console application.
#include "gtest/gtest.h"
#include "descriptor.h"

TEST(testDescriptor, myDescriptorTest)
{
    DecayDescriptor myDescriptor();
    myDescriptor("D0 => KS0 K+ K-");
    EXPECT_EQ("D0 =>KS0 K+ K-", myDescriptor.printDecayDescriptor());	
}

int main(int argc, char ∗∗argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}