#define CATCH_CONFIG_MAIN
#include "catch.hpp.hh"
#include "Simulation.h"

Simulation* sim = new Simulation();

TEST_CASE("Simulation test cases") {
	sim->runSimulation("test1.txt");
	REQUIRE(sim->summary() == 100);
}