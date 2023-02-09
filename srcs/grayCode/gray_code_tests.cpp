/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gray_code_tests.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:23:08 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/09 15:27:36 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ready_set_bool.hpp"

void gray_code_test(void)
{
	std::cout << "Testing gray_code:\n"
			<< "\tpress enter to keep testing this module, n to move to the next one\n";

	__UINT32_TYPE__ a, result;
	auto tester = [&](void) -> void
	{
		a = rand() % 100;
		result = gray_code(a);
		std::cout << "Gray code of " << a << " = " << result << "\n";
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