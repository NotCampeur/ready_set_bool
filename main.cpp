/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:06:44 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/08 15:32:03 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <cmath>

unsigned int adder(unsigned int a, unsigned int b);

void adder_test(void)
{
	std::cout << "Testing adder:\n";

	unsigned int a = rand() % 100;
	unsigned int b = rand() % 100;
	unsigned int result = adder(a, b);
	std::cout << a << " + " << b << " = " << result << " (expected: " << a + b << ")\n";
}

int main()
{
	std::cout << "Welcome in RSB!\n\n";
	srand(time(NULL));
	adder_test();
	return EXIT_SUCCESS;
}