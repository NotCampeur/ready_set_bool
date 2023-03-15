/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplier.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:38:42 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/15 17:45:58 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"

uint32_t multiplier(uint32_t a, uint32_t b)
{
	uint32_t result(0);

	for (uint32_t i(0); i < 32 ; ++i)
	{
		if ((b & (1 << i)) != 0)
			result = adder(result, a << i);
	}
	return result;
}