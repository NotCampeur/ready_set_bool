/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conjunctive_normal_form.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:54:41 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/22 15:28:53 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ready_set_bool.hpp"
#include "rpn_abstract_syntax_tree.hpp"

std::string conjunctive_normal_form(const std::string &formula)
{
	rsb::rpn_abstract_syntax_tree<char, rsb::variable_boolean_token_check> tree;

	try
	{
		tree.build(std::vector<char>(formula.begin(), formula.end()));
		tree.conjunctive_normal_form();
		return tree.formula();
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << NORMAL "\n";
	}

	return formula;
}