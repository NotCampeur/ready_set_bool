/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adder.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:06:48 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/08 15:26:55 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int adder(unsigned int a, unsigned int b)
{
	unsigned int result;

	for (int i(0); i < 32; i++)
	{
		result = (a & i) ^ (b & i);
	}
	return result;
}