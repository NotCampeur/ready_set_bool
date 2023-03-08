/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:01:22 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/08 15:19:19 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"

std::vector<std::vector<__INT32_TYPE__> > powerset(std::vector<__INT32_TYPE__> set)
{
	std::vector<std::vector<__INT32_TYPE__> >	powerset;
	std::vector<__INT32_TYPE__>					subset;

	for (__INT32_TYPE__ i(0), powerset_size(1 << set.size());
		i < powerset_size;
		++i)
	{
		for (std::vector<__INT32_TYPE__>::size_type j(0); j < set.size(); ++j)
			if (i & (1 << j))
				subset.push_back(set[j]);
		powerset.push_back(subset);
		subset.clear();
	}
	return (powerset);
}