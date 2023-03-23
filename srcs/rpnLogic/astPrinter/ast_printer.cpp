/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_printer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:53:22 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/23 01:05:59 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"
#include "rpn_abstract_syntax_tree.hpp"

void ast_printer(void)
{
	std::cout << B_WHITE "Visualizing the AST" NORMAL ":\n"
			<< "\tpress " B_CYAN "enter" NORMAL " to keep testing this module, " B_CYAN "i" NORMAL " to go back to the index\n";

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
			std::cerr << RED << e.what() << NORMAL "\n";
		}
	};

	for (std::string input; input != "i" && std::cin.fail() == false;)
	{
		std::getline(std::cin, input);
		if (input.empty() == true)
			tester();
		else if (input != "i")
			std::cout << RED "Invalid input" NORMAL "\n";
	}
}