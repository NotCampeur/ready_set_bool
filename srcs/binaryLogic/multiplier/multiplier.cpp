/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplier.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:38:42 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/09 14:43:04 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

__UINT32_TYPE__ adder(__UINT32_TYPE__ a, __UINT32_TYPE__ b);

__UINT32_TYPE__ multiplier(__UINT32_TYPE__ a, __UINT32_TYPE__ b)
{
	__UINT32_TYPE__ result(0);

	for (__UINT32_TYPE__ i(0); i < 32 ; ++i)
	{
		if ((b & (1 << i)) != 0)
			result = adder(result, a << i);
	}
	return result;
}