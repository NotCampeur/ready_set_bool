/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:40:46 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/23 01:05:59 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"
#include <limits>

void map_test(void)
{
	std::cout << "Testing " B_WHITE "map" NORMAL ":\n"
			<< "\tpress " B_CYAN "enter" NORMAL " to keep testing this module, " B_CYAN "i" NORMAL " to go back to the index\n";

	uint16_t x, y = 0;
	double result = 0;
	
	auto get_spatial_data = [&](uint16_t &x, uint16_t &y) -> bool
	{
		std::cout << "Enter the x " B_CYAN "coordinate [0;" << std::numeric_limits<uint16_t>::max() << "]" NORMAL " : ";
		std::cin >> x;
		if (std::cin.eof() == true || std::cin.fail() == true)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << RED "Invalid coordinate" NORMAL "\n";
			return false;
		}
		std::cout << "Enter the y " B_CYAN "coordinate [0;" << std::numeric_limits<uint16_t>::max() << "]" NORMAL " : ";
		std::cin >> y;
		if (std::cin.eof() == true || std::cin.fail() == true)
		{
			std::cin.clear(); 
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << RED "Invalid coordinate" NORMAL "\n";
			return false;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return true;
	};

	auto tester = [&](void) -> void
	{
		if (get_spatial_data(x, y) == false)
			return;
		result = map(x, y);
		std::cout.precision(std::numeric_limits<double>::max_digits10);
		std::cout << "The reverse space filling curve of {x=" << x << ", y=" << y << "} is: " << std::fixed << result << "\n";
	};

	for (std::string input; input != "i" && std::cin.fail() == false;)
	{
		std::getline(std::cin, input);
		if (std::cin.fail() == false && input.empty() == true)
			tester();
		else if (input != "i" && std::cin.fail() == false)
			std::cout << RED "Invalid input" NORMAL "\n";
	}
}