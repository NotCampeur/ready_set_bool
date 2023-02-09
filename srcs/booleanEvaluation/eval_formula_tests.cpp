/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_formula_tests.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:49:08 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/09 17:59:52 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"

void eval_formula_test(void)
{
	std::cout << "Testing eval_formula:\n"
			<< "\tpress enter to keep testing this module, n to move to the next one\n";

	bool result;
	std::string formula("101|&");
	auto tester = [&](void) -> void
	{
		result = eval_formula(formula);
		std::cout << "Formula '" << formula << "' eval to: " << result << "\n";
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