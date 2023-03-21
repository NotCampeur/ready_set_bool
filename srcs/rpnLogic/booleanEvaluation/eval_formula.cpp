/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_formula.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:46:39 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/21 15:12:51 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"
#include "rpn_abstract_syntax_tree.hpp"

bool eval_formula(const std::string &formula)
{
	rsb::rpn_abstract_syntax_tree<char, rsb::boolean_token_check> tree;

	if (formula.empty() == true)
		return false;
	try
	{
		tree.build(std::vector<char>(formula.begin(), formula.end()));
		return tree.evaluate();
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << NORMAL "\n";
		return false;
	}
}