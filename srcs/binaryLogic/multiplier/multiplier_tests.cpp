/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplier_tests.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:59:04 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/20 19:34:52 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"

void multiplier_test(void)
{
	std::cout << "Testing " B_WHITE "multiplier" NORMAL ":\n"
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
			{
				uint32_t random_result(rand() % 1000);
				std::cout << B_WHITE << random_result << NORMAL "\n";
				return random_result;
			}
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
		result = multiplier(a, b);
		std::cout << a << " * " << b << " = " << result << " (expected: " << a * b << ")";
		if (result == a * b)
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