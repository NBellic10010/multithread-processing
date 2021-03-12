#define CATCH_CONFIG_MAIN
#include "catch.hpp.hh"
#include "Simulation.h"

Simulation* sim = new Simulation();

int test_simulation(char* filename) {
	sim->runSimulation(filename);
	return sim->gettimeSlice();
}

int test_readin(char* filename) {
	return -1;
}

TEST_CASE("Simulation test cases") {
	REQUIRE(test_simulation("testcases/test_1.txt") == 100);
	REQUIRE(test_readin("testcases/test_2.txt") == -1);
	REQUIRE(test_readin("testcases/test_3.txt") == -1);
	REQUIRE(test_readin("testcases/test_4.txt") == -1);
	REQUIRE(test_simulation("testcases/test_5.txt") == 1128);
}