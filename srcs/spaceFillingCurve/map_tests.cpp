/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:40:46 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/15 20:58:40 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"
#include <limits>

void map_test(void)
{
	std::cout << "Testing \033[1;37mmap\033[0m:\n"
			<< "\tpress \033[1;36menter\033[0m to keep testing this module, \033[1;36mn\033[0m to move to the next one\n";

	uint16_t x, y = 0;
	double result = 0;
	
	auto get_spatial_data = [&](uint16_t &x, uint16_t &y) -> void
	{
		std::cout << "Enter the x \033[1;36mcoordinate [0;" << std::numeric_limits<uint16_t>::max() << "]\033[0m : ";
		std::cin >> x;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.clear();
		std::cout << "Enter the y \033[1;36mcoordinate [0;" << std::numeric_limits<uint16_t>::max() << "]\033[0m : ";
		std::cin >> y;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.clear(); 
	};

	auto tester = [&](void) -> void
	{
		get_spatial_data(x, y);
		result = map(x, y);
		std::cout.precision(std::numeric_limits<double>::max_digits10);
		std::cout << "The reverse space filling curve of {x=" << x << ", y=" << y << "} is: " << std::fixed << result << "\n";
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