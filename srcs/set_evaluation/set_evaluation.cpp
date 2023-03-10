/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_evaluation.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:39:06 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/10 21:05:00 by ldutriez         ###   ########.fr       */
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

	auto create_set_context = [](const rsb::set<rsb::set<__INT32_TYPE__>> &sets) -> rsb::set<__INT32_TYPE__>
	{
		rsb::set<__INT32_TYPE__> result;

		for (auto it(sets.begin()); it != sets.end(); ++it)
			result = result | *it;
		return result;
	};
	
	try
	{
		for (char c: formula)
		{
			if (isalpha(c) != 0)
				build_data.push_back(std::make_pair(c, sets.at(c - 'A')));
			else
				build_data.push_back(std::make_pair(c, rsb::set<__INT32_TYPE__>()));
		}
	}
	catch(const std::exception& e)
	{
		throw std::invalid_argument("Unable to create build data (formula and sets does not match)");
	}

	try
	{
		tree.build(build_data);
		return (tree.set_evaluate(create_set_context(sets)));
	}
	catch(const std::exception& e)
	{
		throw ;
	}
	
	return (rsb::set<__INT32_TYPE__>());
}