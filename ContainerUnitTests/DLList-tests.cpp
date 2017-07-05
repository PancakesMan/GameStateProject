#include "catch.hpp"
#include "DLList.h"

// Create Doubly Linked List of Integers
DLList<int> myIntegers;

TEST_CASE("Test adding items to linked list", "[push_back]") {
	for (int i = 0; i < 10; i++) myIntegers.pushBack(i);
	REQUIRE(myIntegers.count() == 10);
}

TEST_CASE("Test adding items to the front of the list", "[pushFront]") {
	myIntegers.pushFront(100);
	REQUIRE(myIntegers.begin()->value == 100);
}

TEST_CASE("Iterator insert", "[insert]") {
	DLList<int>::iterator it = myIntegers.begin();
	int size = myIntegers.count();

	myIntegers.insert(it, 200);
	REQUIRE(myIntegers.begin()->next->value == 200);
	REQUIRE((size + 1) == myIntegers.count());
}

TEST_CASE("Erase by iterator", "[erase]") {
	int first, last;
	first = myIntegers.begin()->value;
	last = myIntegers.last()->value;

	myIntegers.erase(myIntegers.begin());
	myIntegers.erase(myIntegers.last());

	REQUIRE(first != myIntegers.begin()->value);
	REQUIRE(last != myIntegers.last()->value);
}

TEST_CASE("Remove by value", "[remove]") {
	myIntegers.remove(10);
	for (DLList<int>::iterator it = myIntegers.begin(); it != myIntegers.end(); ++it)
		REQUIRE(it->value != 10);
}

TEST_CASE("Remove last element", "[popBack]") {
	int last = myIntegers.last()->value;
	myIntegers.popBack();

	REQUIRE(myIntegers.last()->value != last);
}

TEST_CASE("Remove first element", "[popFront]") {
	int first = myIntegers.begin()->value;
	myIntegers.popFront();

	REQUIRE(myIntegers.begin()->value != first);
}

TEST_CASE("Test removing even numbers with predicate", "[predicate-remove]") {
	myIntegers.remove([](int i) {return i % 2 == 0; });

	for (auto it = myIntegers.begin(); it != myIntegers.end(); ++it)
		REQUIRE(it->value % 2 != 0);
}

TEST_CASE("Test clearing linked list", "[clear]") {
	myIntegers.clear();
	REQUIRE(myIntegers.count() == 0);
	REQUIRE(myIntegers.first() == myIntegers.end());
	REQUIRE(myIntegers.last() == myIntegers.end());
}

TEST_CASE("Test if linked list is empty", "[empty]") {
	REQUIRE(myIntegers.empty());
}