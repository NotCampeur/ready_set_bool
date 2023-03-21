/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negation_normal_form_tests.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:53:24 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/21 17:22:10 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"

void negation_normal_form_test(void)
{
	std::cout << "Testing " B_WHITE "negation_normal_form" NORMAL ":\n"
			<< "\tpress " B_CYAN "enter" NORMAL " to keep testing this module, " B_CYAN "n" NORMAL " to move to the next one\n";

	std::string result;
	std::string formula;
	auto tester = [&](void) -> void
	{
		formula = get_formula();
		result = negation_normal_form(formula);
		std::cout << "Formula '" << formula << "' become: '" << result << "'\n";
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