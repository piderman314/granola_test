#include "granola.h"
#include <doctest.h>

#include <memory>
#include <string>

test q() {
	auto s = test{ 1, 2 };
	return s;
}

void test_f() {
	auto[a, b] = q();

	auto s = std::make_unique<std::string>("test 1 2 3");
}

int factorial(int number) { return number <= 1 ? number : factorial(number - 1) * number; }

TEST_CASE("testing the factorial function") {
	CHECK(factorial(1) == 1);
	CHECK(factorial(2) == 2);
	CHECK(factorial(3) == 6);
	CHECK(factorial(10) == 3628800);
}