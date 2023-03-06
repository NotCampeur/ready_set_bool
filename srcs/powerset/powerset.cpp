/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:01:22 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/06 19:18:44 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"

std::vector<std::vector<__INT32_TYPE__> > powerset(std::vector<__INT32_TYPE__> set)
{
	std::vector<std::vector<__INT32_TYPE__> >	powerset;
	std::vector<__INT32_TYPE__>					subset;
	__INT32_TYPE__								i;
	std::vector<__INT32_TYPE__>::size_type		j;

	i = 0;
	while (i < (1 << set.size()))
	{
		j = 0;
		while (j < set.size())
		{
			if (i & (1 << j))
				subset.push_back(set[j]);
			j++;
		}
		powerset.push_back(subset);
		subset.clear();
		i++;
	}
	return (powerset);
}