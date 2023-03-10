/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_evaluation_tests.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:50:11 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/10 21:46:54 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"
#include <sstream>

void eval_set_test(void)
{
	std::cout << "Testing \033[1;37meval_set\033[0m:\n"
			<< "\tpress \033[1;36menter\033[0m to keep testing this module, \033[1;36mn\033[0m to move to the next one\n";
	
	rsb::set<rsb::set<__INT32_TYPE__> >	sets;
	std::string formula;
	rsb::set<__INT32_TYPE__>					result;

	auto get_sets = [&](void) -> void
	{
		std::string					input;
		unsigned char				count(0);

		sets.clear();
		std::cout << "Enter \033[1;36msets of integers\033[0m separated by a new line: \n"
		 << "each integer must be separated by a space: (empty line to stop)\n";
		std::cout << "A = ";
		while (std::getline(std::cin, input) && input != "")
		{
			std::stringstream			ss(input);
			__INT32_TYPE__				i;
			rsb::set<__INT32_TYPE__>	set;

			while (ss >> i)
			{
				set.push_back(i);
			}
			sets.push_back(set);
			++count;
			std::cout << static_cast<char>(count + 'A') << " = ";
		}
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

	auto stringify_sets = [&](void) -> std::string
	{
		std::string					result;

		for (rsb::set<rsb::set<__INT32_TYPE__> >::iterator it = sets.begin(); it != sets.end(); it++)
		{
			result += "{";
			result += stringify_set(*it);
			result += "}";
			if (it + 1 != sets.end())
				result += ", ";
		}
		return (result);
	};

	auto tester = [&](void) -> void
	{
		formula = get_formula();
		get_sets();
		try
		{
			result = eval_set(formula, sets);
			std::cout << "formula :\n\t{" << formula << "}\nsets :\n\t {" << stringify_sets()
				<< "}\nresulting set :\n\t{" << stringify_set(result) << "}\n";
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
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