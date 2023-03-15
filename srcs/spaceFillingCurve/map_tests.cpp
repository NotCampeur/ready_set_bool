/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:40:46 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/15 17:47:06 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"

void map_test(void)
{
	std::cout << "Testing \033[1;37mmap\033[0m:\n"
			<< "\tpress \033[1;36menter\033[0m to keep testing this module, \033[1;36mn\033[0m to move to the next one\n";

	auto tester = [&](void) -> void
	{
		std::cout << "Not implemented yet\n";
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