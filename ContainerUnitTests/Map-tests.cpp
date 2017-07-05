#include "catch.hpp"
#include "Map.h"
#include <string>

// Create map of string keys and integer values
Map<std::string, int> myMap;

TEST_CASE("Adding to the map", "[insert]") {
	myMap.Insert("one", 1);
	myMap.Insert("two", 2);
	myMap.Insert("three", 3);
	myMap.Insert("four", 4);
	myMap.Insert("five", 5);
	myMap.Insert("six", 6);
	myMap.Insert("seven", 7);
	myMap.Insert("eight", 8);
	myMap.Insert("nine", 9);
	myMap.Insert("ten", 10);
	REQUIRE(myMap.size() == 10);
}

TEST_CASE("Check all keys", "[Keys]") {
	DynamicArray<std::string> keys = myMap.Keys();

	REQUIRE(keys[0] == "one");
	REQUIRE(keys[1] == "two");
	REQUIRE(keys[2] == "three");
	REQUIRE(keys[3] == "four");
	REQUIRE(keys[4] == "five");
	REQUIRE(keys[5] == "six");
	REQUIRE(keys[6] == "seven");
	REQUIRE(keys[7] == "eight");
	REQUIRE(keys[8] == "nine");
	REQUIRE(keys[9] == "ten");
}

TEST_CASE("Check all values", "[Values]") {
	DynamicArray<int> values = myMap.Values();

	REQUIRE(values[0] == 1);
	REQUIRE(values[1] == 2);
	REQUIRE(values[2] == 3);
	REQUIRE(values[3] == 4);
	REQUIRE(values[4] == 5);
	REQUIRE(values[5] == 6);
	REQUIRE(values[6] == 7);
	REQUIRE(values[7] == 8);
	REQUIRE(values[8] == 9);
	REQUIRE(values[9] == 10);
}

TEST_CASE("set five to be 15", "[subscript operator]") {
	myMap["five"] = 15;
	REQUIRE(myMap["five"] == 15);
}

TEST_CASE("Remove ten", "[remove]") {
	myMap.remove("ten");

	// If the key does not exist
	// trying to access it will
	// create a default value
	REQUIRE(myMap["ten"] == 0);
}

TEST_CASE("Check if key exists", "[exists]") {
	REQUIRE(myMap.Exists("four"));
}

TEST_CASE("clear list", "[clear]") {
	myMap.clear();
	REQUIRE(myMap.size() == 0);
}