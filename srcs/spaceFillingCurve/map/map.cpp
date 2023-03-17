/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:45:52 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/17 15:36:41 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"
#include <cmath>

// Z-order curve bijective function that map multidimensional data to
// one dimension while preserving locality of the data points in
// the closed interval [0; 1]
double map(uint16_t x, uint16_t y)
{
	double result = 0;
	uint32_t int_result(0);

	for (uint8_t i(0); i < 16; ++i)
	{
		int_result = int_result | ((x & (1 << i)) << i);
	}
	for (uint8_t i(0); i < 16; ++i)
	{
		int_result = int_result | ((y & (1 << i)) << (i + 1));
	}
	result = int_result;
	return result / (std::pow(2, 32) -  1);
}