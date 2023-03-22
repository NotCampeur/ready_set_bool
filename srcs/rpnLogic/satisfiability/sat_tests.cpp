/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sat_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:49:12 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/22 15:33:00 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"

void sat_test(void)
{
	std::cout << "Testing " B_WHITE "sat" NORMAL ":\n"
			<< "\tpress " B_CYAN "enter" NORMAL " to keep testing this module, " B_CYAN "n" NORMAL " to move to the next one\n";
	bool result;
	std::string formula;

	auto tester = [&](void) -> void
	{
		formula = get_formula();
		result = sat(formula);
		std::cout << "Formula '" << formula << "' is satisfiable: '" << std::boolalpha << result << "'\n";
	};

	for (std::string input; input != "n" && std::cin.fail() == false;)
	{
		std::getline(std::cin, input);
		if (input.empty() == true)
			tester();
		else if (input != "n")
			std::cout << RED "Invalid input" NORMAL "\n";
	}
	std::cout << std::noboolalpha;
}