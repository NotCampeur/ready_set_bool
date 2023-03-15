/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   truth_table.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 04:06:07 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/16 15:28:52 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"
#include "rpn_abstract_syntax_tree.hpp"
#include <map>
#include <algorithm>

// Print the truth table of a formula
// The accepted formula is a string of characters
// The variables are the characters from A to Z
void print_truth_table(const std::string &formula)
{
	rsb::rpn_abstract_syntax_tree<char, rsb::variable_boolean_token_check> tree;

	if (formula.empty() == true)
		return;
	try 
	{
		tree.build(std::vector<char>(formula.begin(), formula.end()));
		tree.print_truth_table();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return;
	}
}