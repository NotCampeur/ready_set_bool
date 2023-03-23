/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset_tests.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:04:10 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/23 01:05:59 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"
#include <sstream>

void powerset_test(void)
{
	std::cout << "Testing " B_WHITE "powerset" NORMAL ":\n"
			<< "\tpress " B_CYAN "enter" NORMAL " to keep testing this module, " B_CYAN "i" NORMAL " to go back to the index\n";
	
	rsb::set<int32_t>	set;
	rsb::set<rsb::set<int32_t> >	powerset_result;

	auto get_set = [&](void) -> void
	{
		std::string					input;

		set.clear();
		std::cout << "Enter " B_CYAN "integers" NORMAL " separated by a " B_CYAN "space" NORMAL ": ";
		std::getline(std::cin, input);
		std::stringstream			ss(input);
		int32_t				i;

		while (ss >> i)
			set.push_back(i);
	};

	auto stringify_set = [&](rsb::set<int32_t> set) -> std::string
	{
		std::string					result;

		for (rsb::set<int32_t>::iterator it = set.begin(); it != set.end(); it++)
		{
			result += std::to_string(*it);
			if (it + 1 != set.end())
				result += ", ";
		}
		return (result);
	};

	auto stringify_powerset = [&](rsb::set<rsb::set<int32_t> > powerset) -> std::string
	{
		std::string					result;
		static std::string			colors[] = {B_GREEN, B_YELLOW, B_BLUE, B_PURPLE, B_CYAN, B_WHITE};
		unsigned int				color_index = 0;
		
		for (rsb::set<rsb::set<int32_t> >::iterator it = powerset.begin(); it != powerset.end(); it++)
		{
			result += colors[color_index % 6] + "{" +
				stringify_set(*it) +
				 "}" NORMAL;
			if (it + 1 != powerset.end())
				result += ",\n\t";
			++color_index;
		}
		return (result);
	};
	
	auto tester = [&](void) -> void
	{
		get_set();
		powerset_result = powerset(set);
		std::cout << "set :\n\t{" << stringify_set(set) << "}\npowerset :\n\t {" << stringify_powerset(powerset_result) << "}\n";
	};

	for (std::string input; input != "i" && std::cin.fail() == false;)
	{
		std::getline(std::cin, input);
		if (input.empty() == true)
			tester();
		else if (input != "i")
			std::cout << RED "Invalid input" NORMAL "\n";
	}
}