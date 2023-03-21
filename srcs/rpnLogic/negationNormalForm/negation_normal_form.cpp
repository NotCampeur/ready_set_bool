/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negation_normal_form.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:05:23 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/21 17:23:23 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"
#include "rpn_abstract_syntax_tree.hpp"

std::string negation_normal_form(const std::string &formula)
{
	rsb::rpn_abstract_syntax_tree<char, rsb::variable_boolean_token_check> tree;

	try
	{
		tree.build(std::vector<char>(formula.begin(), formula.end()));
		tree.negation_normal_form();
		return tree.formula();
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << NORMAL "\n";
	}

	return formula;
}