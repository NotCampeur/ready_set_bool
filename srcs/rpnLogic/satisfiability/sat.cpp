/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:46:54 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/23 03:15:03 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"
#include "rpn_abstract_syntax_tree.hpp"

bool sat(const std::string & formula)
{
	rsb::rpn_abstract_syntax_tree<char, rsb::variable_boolean_token_check> ast;

	if (formula.empty() == true)
		return false;
	try
	{
		ast.build(std::vector<char>(formula.begin(), formula.end()));
		return ast.is_satisfiable();
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << NORMAL "\n";
	}
	return false;
}