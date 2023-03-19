/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gray_code_tests.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:23:08 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/19 17:14:38 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ready_set_bool.hpp"

void gray_code_test(void)
{
	std::cout << "Testing " B_WHITE "gray_code" NORMAL ":\n"
			<< "\tpress " B_CYAN "enter" NORMAL " to keep testing this module, " B_CYAN "n" NORMAL " to move to the next one\n";

	uint32_t a, result;
	auto tester = [&](void) -> void
	{
		a = rand() % 100;
		result = gray_code(a);
		std::cout << "Gray code of " << a << " = " << result << "\n";
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