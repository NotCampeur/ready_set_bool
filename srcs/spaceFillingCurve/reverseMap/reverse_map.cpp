/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_map.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 21:22:40 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/17 15:52:57 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"
#include <cmath>

std::pair<uint16_t, uint16_t> reverse_map(double data)
{
	uint32_t int_data = static_cast<uint32_t>(data * (std::pow(2, 32) - 1));
	uint16_t x(0);
	uint16_t y(0);

	for (uint8_t i(0); i < 16; ++i)
	{
		x = x | ((int_data & (1 << (i * 2))) >> i);
	}
	for (uint8_t i(0); i < 16; ++i)
	{
		y = y | ((int_data & (1 << (i * 2 + 1))) >> (i + 1));
	}
	return std::make_pair(x, y);
}
