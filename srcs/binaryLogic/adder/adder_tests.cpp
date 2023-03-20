/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adder_tests.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:54:30 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/20 17:21:23 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"

void adder_test(void)
{
	std::cout << "Testing " B_WHITE "adder" NORMAL ":\n"
			<< "\tpress " B_CYAN "enter" NORMAL " to keep testing this module, " B_CYAN "n" NORMAL " to move to the next one\n";

	uint32_t a, b, result;

	auto get_operand = [&](void) -> uint32_t
	{
		std::string input;
		while (std::cin.fail() == false)
		{
			std::cout << "Enter an " B_CYAN "operand" NORMAL " (empty for random): ";
			std::getline(std::cin, input);
			if (input.empty() == true && std::cin.fail() == false)
				return rand() % std::numeric_limits<uint32_t>::max();
			try
			{
				return std::stoul(input);
			}
			catch(...)
			{
				std::cout << RED "Invalid input" NORMAL "\n";
			}
		}
		return 0;
	};
	
	auto tester = [&](void) -> void
	{
		a = get_operand();
		b = get_operand();
		result = adder(a, b);
		std::cout << a << " + " << b << " = " << result << " (expected: " << a + b << ")";
		if (result == a + b)
			std::cout << " " GREEN "OK" NORMAL "\n";
		else
			std::cout << " " RED "KO" NORMAL "\n";
	};

	for (std::string input; input != "n" && std::cin.fail() == false;)
	{
		std::getline(std::cin, input);
		if (input.empty() == true)
			tester();
		else if (input != "n")
			std::cout << RED "Invalid input" NORMAL "\n";
	}
}