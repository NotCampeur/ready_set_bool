/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conjunctive_normal_form_tests.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:56:15 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/06 16:43:18 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"

void conjunctive_normal_form_test(void)
{
	std::cout << "Testing \033[1;37mconjunctive_normal_form\033[0m:\n"
			<< "\tpress \033[1;36menter\033[0m to keep testing this module, \033[1;36mn\033[0m to move to the next one\n";

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