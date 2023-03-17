/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_map_tests.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 21:14:36 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/17 18:41:13 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"
#include <limits>

void reverse_map_test(void)
{
	std::cout << "Testing \033[1;37mreverse_map\033[0m:\n"
			<< "\tpress \033[1;36menter\033[0m to keep testing this module, \033[1;36mn\033[0m to move to the next one\n";

	double data(0);
	std::pair<uint16_t , uint16_t> coordinates;
	
	auto get_spatial_data = [&](void) -> bool
	{
		std::cout << "Enter the \033[1;36mone dimension value [0;1]\033[0m : ";
		std::cin >> data;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (std::cin.eof() == true || std::cin.fail() == true)
		{
			std::cin.clear();
			return false;
		}
		if (data < 0 || data > 1)
		{
			std::cin.clear();
			std::cin.putback('\n');
			return false;
		}
		return true;
	};

	auto tester = [&](void) -> void
	{
		if (get_spatial_data() == false)
			return;
		coordinates = reverse_map(data);
		std::cout.precision(std::numeric_limits<double>::max_digits10);
		std::cout << "The space filling curve of " << std::fixed << data
		<< " is: {x=" << coordinates.first << ", y=" << coordinates.second << "}\n";
	};

	for (std::string input; input != "n" && std::cin.fail() == false;)
	{
		std::getline(std::cin, input);
		if (std::cin.fail() == false && input.empty() == true)
			tester();
		else if (input != "n")
			std::cout << "\033[0;31mInvalid command : " << input << "\033[0m\n";
	}
}