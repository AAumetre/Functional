#include <iostream>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Def.h"

TEST_CASE("Increment a value"){
    CHECK_EQ(2, 2);
}

/*
int main(int argc, char** argv) {
	std::cout << "Hello world" << std::endl;

	std::vector< int > my_numbers{ 1, 2, 3, 4, 5, 6, 7, 8, 9};
	// Does the comparison in a lambda
	auto sorted_numbers = pure::filter(my_numbers,
			[](int n) {return (n % 2 == 0); });
	for (const auto& num : sorted_numbers )
		std::cout << num;
	std::cout << std::endl;

	// Uses the lambda to call an actual function ...
	sorted_numbers = pure::filter(my_numbers,
			[](int n) {return pure::ff_pair(n); });
	for (const auto& num : sorted_numbers)
		std::cout << num;
	std::cout << std::endl;

	// Demo of tuples
	const std::tuple< int, int > augmented = pure::incrementBoth(1, 2);
	std::cout << std::get<0>( augmented ) << " "
		<< std::get<1>( augmented ) << std::endl;

	auto incrBef = []( int& value ) {
		return ++value;
	};
	auto incrAft = [](int& value) {
		return value++;
	};

	int val1 = 0, val2 = 0;
	std::cout << "Initial: " << val1 << " => "
		<< incrBef(val1) << " from " << val1 << std::endl;
	std::cout << "Initial: " << val2 << " => "
		<< incrAft(val2) << " from " << val2 << std::endl;
	// 1 from 1
	// 0 from 1
	return 0;
}*/
