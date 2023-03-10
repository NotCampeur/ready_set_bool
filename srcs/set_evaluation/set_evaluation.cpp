/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_evaluation.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:39:06 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/10 05:48:10 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"
#include "rpn_abstract_syntax_tree.hpp"

rsb::set<__INT32_TYPE__> eval_set(std::string &formula,
								rsb::set<rsb::set<__INT32_TYPE__> > &sets)
{
	rsb::rpn_abstract_syntax_tree<
		std::pair<char, rsb::set<__INT32_TYPE__> >,
		rsb::set_variable_boolean_token_check
		> tree;

	std::vector<std::pair<char, rsb::set<__INT32_TYPE__> > > build_data;

	for (char c: formula)
	{
		if (isalpha(c) == true)
			build_data.push_back(std::make_pair(c, sets[c - 'A']));
		else
			build_data.push_back(std::make_pair(c, rsb::set<__INT32_TYPE__>()));
	}

	try
	{
		tree.build(build_data);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return (rsb::set<__INT32_TYPE__>());
}