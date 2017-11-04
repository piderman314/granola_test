#include "granola.h"

test q() {
	auto s = test{ 1, 2 };
	return s;
}

void test_f() {
	const auto[a, b] = q();
}