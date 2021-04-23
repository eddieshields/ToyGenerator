#include "catch.hpp"

#include "clock.h"

#include <chrono>
#include <thread>

TEST_CASE( "Test Clock", "[Clock]") {
  SECTION("Check clock works") {
    Clock::Start();
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));
    Clock::Stop();
    Clock::Print("test clock works");
  }
}