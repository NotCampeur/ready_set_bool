/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ready_set_bool.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:56:02 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/09 15:03:50 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READY_SET_BOOL_HPP
# define READY_SET_BOOL_HPP

// ALGEBRA FUNCTIONS

__UINT32_TYPE__ adder(__UINT32_TYPE__ a, __UINT32_TYPE__ b);
__UINT32_TYPE__ multiplier(__UINT32_TYPE__ a, __UINT32_TYPE__ b);

// TESTING FUNCTIONS

# include <iostream>
# include <limits>
void adder_test(void);
void multiplier_test(void);

#endif