/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negation_normal_form.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:05:23 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/16 17:52:47 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "rpn_abstract_syntax_tree.hpp"

std::string negation_normal_form(const std::string &formula)
{
	std::string result;
	rsb::rpn_abstract_syntax_tree<char, rsb::variable_boolean_token_check> tree;

	try
	{
		tree.build(std::vector<char>(formula.begin(), formula.end()));
		tree.negation_normal_form();
		result = tree.formula();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return result;
}