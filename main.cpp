/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:06:44 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/08 17:26:03 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>

unsigned int adder(unsigned int a, unsigned int b);

void adder_test(void)
{
	std::cout << "Testing adder:\n";

	unsigned int a = rand() % 100;
	unsigned int b = rand() % 100;
	unsigned int result = adder(a, b);
	std::cout << a << " + " << b << " = " << result << " (expected: " << a + b << ")\n";
}

void seed_selection(void)
{
	std::string input;
	unsigned int seed;
	
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
	return EXIT_SUCCESS;
}