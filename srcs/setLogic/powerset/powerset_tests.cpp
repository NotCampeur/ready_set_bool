/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset_tests.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:04:10 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/09 16:48:35 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"
#include <sstream>

void powerset_test(void)
{
	std::cout << "Testing \033[1;37mpowerset\033[0m:\n"
			<< "\tpress \033[1;36menter\033[0m to keep testing this module, \033[1;36mn\033[0m to move to the next one\n";
	
	rsb::set<__INT32_TYPE__>	set;
	rsb::set<rsb::set<__INT32_TYPE__> >	powerset_result;

	auto get_set = [&](void) -> void
	{
		std::string					input;

		set.clear();
		std::cout << "Enter a set of integers separated by a space: ";
		std::getline(std::cin, input);
		std::stringstream			ss(input);
		__INT32_TYPE__				i;

		while (ss >> i)
			set.push_back(i);
	};

	auto stringify_set = [&](rsb::set<__INT32_TYPE__> set) -> std::string
	{
		std::string					result;

		for (rsb::set<__INT32_TYPE__>::iterator it = set.begin(); it != set.end(); it++)
		{
			result += std::to_string(*it);
			if (it + 1 != set.end())
				result += ", ";
		}
		return (result);
	};

	auto stringify_powerset = [&](rsb::set<rsb::set<__INT32_TYPE__> > powerset) -> std::string
	{
		std::string					result;

		for (rsb::set<rsb::set<__INT32_TYPE__> >::iterator it = powerset.begin(); it != powerset.end(); it++)
		{
			result += "{";
			result += stringify_set(*it);
			result += "}";
			if (it + 1 != powerset.end())
				result += ", ";
		}
		return (result);
	};
	
	auto tester = [&](void) -> void
	{
		get_set();
		powerset_result = powerset(set);
		std::cout << "set :\n\t{" << stringify_set(set) << "}\npowerset :\n\t {" << stringify_powerset(powerset_result) << "}\n";
	};

	for (std::string input; input != "n" && std::cin.fail() == false;)
	{
		std::getline(std::cin, input);
		if (input.empty() == true)
			tester();
		else if (input != "n")
			std::cout << "Invalid command : " << input << "\n";
	}
}