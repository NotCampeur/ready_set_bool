/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:01:22 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/09 16:48:28 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"

rsb::set<rsb::set<__INT32_TYPE__> > powerset(rsb::set<__INT32_TYPE__> set)
{
	rsb::set<rsb::set<__INT32_TYPE__> >	powerset;
	rsb::set<__INT32_TYPE__>					subset;

	for (__INT32_TYPE__ i(0), powerset_size(1 << set.size());
		i < powerset_size;
		++i)
	{
		for (rsb::set<__INT32_TYPE__>::size_type j(0); j < set.size(); ++j)
			if (i & (1 << j))
				subset.push_back(set[j]);
		powerset.push_back(subset);
		subset.clear();
	}
	return (powerset);
}