/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplier_tests.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:59:04 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/15 17:22:49 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"

void multiplier_test(void)
{
	std::cout << "Testing \033[1;37mmultiplier\033[0m:\n"
			<< "\tpress \033[1;36menter\033[0m to keep testing this module, \033[1;36mn\033[0m to move to the next one\n";

	uint32_t a, b, result;
	auto tester = [&](void) -> void
	{
		a = rand() % 100;
		b = rand() % 100;
		result = multiplier(a, b);
		std::cout << a << " * " << b << " = " << result << " (expected: " << a * b << ")\n";
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