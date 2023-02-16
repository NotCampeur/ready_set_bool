/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_printer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:53:22 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/16 17:15:03 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "rpn_abstract_syntax_tree.hpp"

static std::string get_formula(void)
{
	std::string formula;
	std::cout << "Enter a formula to evaluate: ";
	std::getline(std::cin, formula);
	return formula;
}

void ast_printer(void)
{
	std::cout << "Visualizing the AST:\n"
			<< "\tpress enter to keep testing this module, n to move to the next one\n";

	rsb::rpn_abstract_syntax_tree<char, rsb::variable_boolean_token_check> tree;
	std::string formula;
	auto tester = [&](void) -> void
	{
		formula = get_formula();
		try 
		{
			tree.build(std::vector<char>(formula.begin(), formula.end()));
			std::cout << "AST storing the formula {" << tree.formula() << "}:\n";
			tree.print();
		}
		catch(const std::exception& e)
		{
			tree.print();
			std::cerr << e.what() << '\n';
		}
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