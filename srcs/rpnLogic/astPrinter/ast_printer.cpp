/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_printer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:53:22 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/06 16:44:10 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"
#include "rpn_abstract_syntax_tree.hpp"

void ast_printer(void)
{
	std::cout << "\033[1;37mVisualizing the AST\033[0m:\n"
			<< "\tpress \033[1;36menter\033[0m to keep testing this module, \033[1;36mn\033[0m to move to the next one\n";

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