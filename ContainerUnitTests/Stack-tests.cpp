#include "catch.hpp"
#include "Stack.h"

Stack<int> integerStack;

TEST_CASE("Test pushing item onto stack", "[push]") {
	for (int i = 1; i <= 5; i++)
		integerStack.push(i);

	REQUIRE(integerStack.count() == 5);
}

TEST_CASE("Test popping item off stack", "[pop]") {
	integerStack.pop();
	REQUIRE(integerStack.count() == 4);
}

TEST_CASE("Test getting top element on stack", "[top]") {
	REQUIRE(integerStack.top() == 4);
}

TEST_CASE("Test clearing the stack", "[clear]") {
	integerStack.clear();
	REQUIRE(integerStack.empty());
}