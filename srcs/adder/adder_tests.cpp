/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adder_tests.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:54:30 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/09 14:58:01 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"

void adder_test(void)
{
	std::cout << "Testing adder:\n"
			<< "\tpress enter to keep testing this module, n to move to the next one\n";

	__UINT32_TYPE__ a, b, result;
	auto tester = [&](void) -> void
	{
		a = rand() % std::numeric_limits<__UINT32_TYPE__>::max();
		b = rand() % std::numeric_limits<__UINT32_TYPE__>::max();
		result = adder(a, b);
		std::cout << a << " + " << b << " = " << result << " (expected: " << a + b << ")\n";
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