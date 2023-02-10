/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   truth_table_tests.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 04:22:09 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/10 04:31:29 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"

void print_truth_table_test(void)
{
	std::cout << "Testing truth_table:\n"
			<< "\tpress enter to keep testing this module, n to move to the next one\n";

	auto get_formula = [&]() -> std::string
	{
		std::string formula;
		std::cout << "Enter a formula to see the truth table: ";
		std::getline(std::cin, formula);
		return formula;
	};

	auto tester = [&](void) -> void
	{
		print_truth_table(get_formula());
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