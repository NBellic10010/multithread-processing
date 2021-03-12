#define CATCH_CONFIG_MAIN
#include "catch.hpp.hh"
#include "Simulation.h"

Simulation* sim = new Simulation();

int test(char* filename) {
	sim->runSimulation(filename);
	return sim->gettimeSlice();
}

TEST_CASE("Simulation test cases") {
	
	REQUIRE(test("test_1.txt") == 100);
	REQUIRE(test("test_2.txt") == 379);
	REQUIRE(test("test_3.txt") == 237);
	REQUIRE(test("test_4.txt") == 543);
	REQUIRE(test("test_5.txt") == 1128);
}