/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adder.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:06:48 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/08 17:38:13 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int adder(unsigned int a, unsigned int b)
{
	unsigned int result(0);
	unsigned int tmp(0);

	for (unsigned int i(0); i < 32 ; ++i)
	{
		tmp = 1 << i;
		result |= (a & tmp) ^ (b & tmp);
	}
	return result;
}