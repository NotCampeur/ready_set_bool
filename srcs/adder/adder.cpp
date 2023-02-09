/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adder.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:06:48 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/09 14:32:07 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

__UINT32_TYPE__ adder(__UINT32_TYPE__ a, __UINT32_TYPE__ b)
{
	__UINT32_TYPE__ result(0);
	__UINT32_TYPE__ tmp(0);
	__UINT32_TYPE__ carry(0);

	for (__UINT32_TYPE__ i(0); i < 32 ; ++i)
	{
		tmp = 1 << i;
		result = result | ((a & tmp) ^ (b & tmp) ^ carry);
		carry = ((a & tmp) & (b & tmp)) | ((a & tmp) & carry) | ((b & tmp) & carry);
		carry = carry << 1;
	}
	return result;
}