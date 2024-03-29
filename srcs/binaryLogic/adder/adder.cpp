/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adder.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:06:48 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/15 17:46:16 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdint>

uint32_t adder(uint32_t a, uint32_t b)
{
	uint32_t result(0);
	uint32_t tmp(0);
	uint32_t carry(0);

	for (uint32_t i(0); i < 32 ; ++i)
	{
		tmp = 1 << i;
		result = result | ((a & tmp) ^ (b & tmp) ^ carry);
		carry = ((a & tmp) & (b & tmp)) | ((a & tmp) & carry) | ((b & tmp) & carry);
		carry = carry << 1;
	}
	return result;
}