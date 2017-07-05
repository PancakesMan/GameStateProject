#include <iostream>

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

int main(char argc, const char* argv[])
{
	int result = Catch::Session().run(argc, argv);
	system("pause");
}