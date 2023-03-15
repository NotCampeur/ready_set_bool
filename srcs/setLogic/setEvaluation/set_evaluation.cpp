/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_evaluation.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:39:06 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/15 17:23:17 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"
#include "rpn_abstract_syntax_tree.hpp"

rsb::set<int32_t> eval_set(std::string &formula,
								rsb::set<rsb::set<int32_t> > &sets)
{
	rsb::rpn_abstract_syntax_tree<
		std::pair<char, rsb::set<int32_t> >,
		rsb::set_variable_boolean_token_check
		> tree;

	std::vector<std::pair<char, rsb::set<int32_t> > > build_data;

	auto create_set_context = [](const rsb::set<rsb::set<int32_t>> &sets) -> rsb::set<int32_t>
	{
		rsb::set<int32_t> result;

		for (auto it(sets.begin()); it != sets.end(); ++it)
			result = result | *it;
		return result;
	};
	
	try
	{
		for (char c: formula)
		{
			if (isupper(c) != 0)
				build_data.push_back(std::make_pair(c, sets.at(c - 'A')));
			else
				build_data.push_back(std::make_pair(c, rsb::set<int32_t>()));
		}
	}
	catch(const std::exception& e)
	{
		throw std::invalid_argument("\033[0;31mUnable to create build data (formula and sets does not match)\033[0m");
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
	
	return (rsb::set<int32_t>());
}