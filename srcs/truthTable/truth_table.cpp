/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   truth_table.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 04:06:07 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/11 13:28:07 by ldutriez         ###   ########.fr       */
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
	rsb::rpn_abstract_syntax_tree<char, rsb::boolean_token_check> tree;
	std::map<char, bool> variables;
	bool result(false);
	size_t max_variations(0);
	std::string formula_variation;
	
	if (formula.empty() == true)
		return;
	for (char c : formula)
		if (c >= 'A' && c <= 'Z')
			variables[c] = false;
	std::cout << "Formula '" << formula << "' truth table\n";
	for (std::pair<char, bool> pair : variables)
		std::cout << "| " << pair.first << " ";
	std::cout << "| = |\n";
	for (std::map<char, bool>::size_type i(0); i < variables.size(); i++)
		std::cout << "|---";
	std::cout << "|---|\n";
	max_variations = 1 << variables.size();
	for (std::map<char, bool>::size_type i(0); i < max_variations; ++i)
	{
		formula_variation = formula;
		for (std::map<char, bool>::iterator it(variables.begin());
			it != variables.end(); ++it)
		{
			it->second = (i & (1 << (std::distance(it, variables.end()) - 1))) != 0;
			std::cout << "| " << it->second << " ";
			std::replace(formula_variation.begin(), formula_variation.end(),
				it->first, it->second == true ? '1' : '0');
		}
		try
		{
			tree.build(std::vector<char>(formula_variation.begin(), formula_variation.end()));
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
			return;
		}
		result = tree.evaluate();
		std::cout << "| " << result << " |\n";
	}
}