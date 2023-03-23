/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sat_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:49:12 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/23 01:05:59 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"

void sat_test(void)
{
	std::cout << "Testing " B_WHITE "sat" NORMAL ":\n"
			<< "\tpress " B_CYAN "enter" NORMAL " to keep testing this module, " B_CYAN "i" NORMAL " to go back to the index\n";
	bool result;
	std::string formula;

	auto tester = [&](void) -> void
	{
		formula = get_formula();
		result = sat(formula);
		std::cout << "Formula '" << formula << "' is satisfiable: '" << std::boolalpha << result << "'\n";
	};

	for (std::string input; input != "i" && std::cin.fail() == false;)
	{
		std::getline(std::cin, input);
		if (input.empty() == true)
			tester();
		else if (input != "i")
			std::cout << RED "Invalid input" NORMAL "\n";
	}
	std::cout << std::noboolalpha;
}