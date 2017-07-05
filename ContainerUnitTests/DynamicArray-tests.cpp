#include "catch.hpp"
#include "DynamicArray.h"

// Create DynamicArray with capacity of 10
DynamicArray<int> myIntegers(10);

TEST_CASE("Add more items than capacity", "[push_back]") {
	for (int i = 0; i < 20; i++) myIntegers.AddToEnd(i);
	REQUIRE(myIntegers.Size() == 20);
}

TEST_CASE("Remove from end", "[pop_back]") {
	int size = myIntegers.Size();
	myIntegers.RemoveFromEnd();
	REQUIRE((size - myIntegers.Size()) == 1);
}

TEST_CASE("Remove from index", "[Remove]") {
	int elem0 = myIntegers[0];
	myIntegers.Remove(0);
	REQUIRE(elem0 != myIntegers[0]);
}

TEST_CASE("Copy constructor", "[copy ctor]") {
	DynamicArray<int> copyOfIntegers(myIntegers);
	for (int i = 0; i < copyOfIntegers.Size(); i++)
		REQUIRE(copyOfIntegers[i] == myIntegers[i]);
}

TEST_CASE("copy assignment", "[copy assignment]") {
	DynamicArray<int> copyOfIntegers;
	copyOfIntegers = myIntegers;
	for (int i = 0; i < copyOfIntegers.Size(); i++)
		REQUIRE(copyOfIntegers[i] == myIntegers[i]);
}

TEST_CASE("Clear the array", "[clear]") {
	myIntegers.Clear();
	REQUIRE(myIntegers.Size() == 0);
}