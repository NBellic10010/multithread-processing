#define CATCH_CONFIG_MAIN
#include "catch.hpp.hh"
#include "Simulation.h"

Simulation* sim = new Simulation();

int test(char* filename) {
	sim->runSimulation(filename);
	return sim->gettimeSlice();
}

TEST_CASE("Simulation test cases") {
	REQUIRE(test("testcases/test_1.txt") == 100);
	REQUIRE(test("testcases/test_2.txt") == 379);
	REQUIRE(test("testcases/test_3.txt") == 237);
	REQUIRE(test("testcases/test_4.txt") == 543);
	REQUIRE(test("testcases/test_5.txt") == 1128);
}