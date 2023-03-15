/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gray_code_tests.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:23:08 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/06 16:43:18 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ready_set_bool.hpp"

void gray_code_test(void)
{
	std::cout << "Testing \033[1;37mgray_code\033[0m:\n"
			<< "\tpress \033[1;36menter\033[0m to keep testing this module, \033[1;36mn\033[0m to move to the next one\n";

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