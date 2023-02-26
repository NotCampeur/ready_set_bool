/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conjunctive_normal_form_tests.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:56:15 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/26 14:56:55 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"

void conjunctive_normal_form_test(void)
{
	std::cout << "Testing conjunctive_normal_form:\n"
			<< "\tpress enter to keep testing this module, n to move to the next one\n";

	std::string result;
	std::string formula;
	auto tester = [&](void) -> void
	{
		formula = get_formula();
		result = conjunctive_normal_form(formula);
		std::cout << "Formula '" << formula << "' become: '" << result << "'\n";
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