/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gray_code_tests.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:23:08 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/21 15:02:59 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ready_set_bool.hpp"

void gray_code_test(void)
{
	std::cout << "Testing " B_WHITE "gray_code" NORMAL ":\n"
			<< "\tpress " B_CYAN "enter" NORMAL " to keep testing this module, " B_CYAN "n" NORMAL " to move to the next one\n";

	uint32_t a, result;

	auto get_operand = [&](void) -> uint32_t
	{
		std::string input;
		while (std::cin.fail() == false)
		{
			std::cout << "Enter an " B_CYAN "operand" NORMAL " (empty for random): ";
			std::getline(std::cin, input);
			if (input.empty() == true && std::cin.fail() == false)
			{
				uint32_t random_result(rand() % std::numeric_limits<uint32_t>::max());
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
		result = gray_code(a);
		std::cout << "Gray code of " << a << " = " << result << '\n';
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