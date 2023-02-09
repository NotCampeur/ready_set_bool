/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adder.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:06:48 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/09 14:25:54 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int adder(unsigned int a, unsigned int b)
{
	unsigned int result(0);
	unsigned int tmp(0);
	unsigned int carry(0);

	for (unsigned int i(0); i < 32 ; ++i)
	{
		tmp = 1 << i;
		result = result | ((a & tmp) ^ (b & tmp) ^ carry);
		carry = ((a & tmp) & (b & tmp)) | ((a & tmp) & carry) | ((b & tmp) & carry);
		carry = carry << 1;
	}
	return result;
}