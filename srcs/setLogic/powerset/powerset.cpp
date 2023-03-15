/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:01:22 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/15 17:23:17 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"

rsb::set<rsb::set<int32_t> > powerset(rsb::set<int32_t> set)
{
	rsb::set<rsb::set<int32_t> >	powerset;
	rsb::set<int32_t>					subset;

	for (int32_t i(0), powerset_size(1 << set.size());
		i < powerset_size;
		++i)
	{
		for (rsb::set<int32_t>::size_type j(0); j < set.size(); ++j)
			if (i & (1 << j))
				subset.push_back(set[j]);
		powerset.push_back(subset);
		subset.clear();
	}
	return (powerset);
}