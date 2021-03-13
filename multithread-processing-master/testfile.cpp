#define CATCH_CONFIG_MAIN
#include "catch.hpp.hh"
#include "Simulation.h"

Simulation* sim = new Simulation();

int test_simulation(char* filename) {
	sim->runSimulation(filename);
	return sim->gettimeSlice();
}

int test_readin(std::string listserial) {
	Process* process = new Process();
	return process->setlist(listserial);
}

TEST_CASE("Simulation test cases") {
	REQUIRE(test_simulation("testcases/test_1.txt") == 100);
	REQUIRE(test_readin("-2 6 -19 3 -11 7 -11 9") == -1);
	REQUIRE(test_readin("20 7 -10 9 -12 7 -32 0") == -2);
	REQUIRE(test_readin("6 8 -12 6 -10 -4 -22 7") == -3);
	REQUIRE(test_simulation("testcases/test_5.txt") == 1128);
}