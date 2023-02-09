/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:06:44 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/09 14:50:35 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <limits>

__UINT32_TYPE__ adder(__UINT32_TYPE__ a, __UINT32_TYPE__ b);
__UINT32_TYPE__ multiplier(__UINT32_TYPE__ a, __UINT32_TYPE__ b);

void adder_test(void)
{
	std::cout << "Testing adder:\n"
			<< "\tpress enter to keep testing this module, n to move to the next one\n";

	__UINT32_TYPE__ a, b, result;
	auto tester = [&](void) -> void
	{
		a = rand() % std::numeric_limits<__UINT32_TYPE__>::max();
		b = rand() % std::numeric_limits<__UINT32_TYPE__>::max();
		result = adder(a, b);
		std::cout << a << " + " << b << " = " << result << " (expected: " << a + b << ")\n";
	};

	for (std::string input; input != "n" && std::cin.fail() == false;)
	{
		std::getline(std::cin, input);
		if (input.empty() == true)
			tester();
		else if (input != "n")
			std::cout << "Invalid command : " << input << "\n";
	}
}

void multiplier_test(void)
{
	std::cout << "Testing multiplier:\n"
			<< "\tpress enter to keep testing this module, n to move to the next one\n";

	__UINT32_TYPE__ a, b, result;
	auto tester = [&](void) -> void
	{
		a = rand() % 100;
		b = rand() % 100;
		result = multiplier(a, b);
		std::cout << a << " * " << b << " = " << result << " (expected: " << a * b << ")\n";
	};

	for (std::string input; input != "n" && std::cin.fail() == false;)
	{
		std::getline(std::cin, input);
		if (input.empty() == true)
			tester();
		else if (input != "n")
			std::cout << "Invalid command : " << input << "\n";
	}
}

void seed_selection(void)
{
	std::string input;
	__UINT32_TYPE__ seed;
	
	std::cout << "Enter a seed if you want to use a specific seed, or just press enter to use the current time as seed: ";
	std::getline(std::cin, input);
	try
	{
		seed = std::stoul(input);
	}
	catch(...)
	{
		input.clear();
	}
	
	if (std::cin.fail() || input.empty() || input == "\n")
		srand(time(NULL));
	else
		srand(seed);
	std::cin.clear();
}

int main()
{
	std::cout << "Welcome in RSB!\n\n";
	seed_selection();
	adder_test();
	multiplier_test();
	return EXIT_SUCCESS;
}