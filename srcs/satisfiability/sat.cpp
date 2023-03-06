/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:46:54 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/06 16:03:38 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"
#include "rpn_abstract_syntax_tree.hpp"

bool sat(std::string & formula)
{
	bool result(false);

	if (formula.empty() == true)
		return result;
	return result;
}