/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_set.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:27:43 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/09 16:00:35 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READY_SET_BOOL_MATH_SET_HPP
# define READY_SET_BOOL_MATH_SET_HPP

#include <vector>
#include <memory>

namespace rsb
{
	template < class T, class Alloc = std::allocator<T> >
	class set: public std::vector<T, Alloc>
	{
		public:
			set() : std::vector<T, Alloc>()
			{}

			set(const set & src) : std::vector<T, Alloc>(src)
			{}

			set & operator=(const set & src)
			{
				if (this == &src)
					return (*this);
				std::vector<T, Alloc>::operator=(src);
				return (*this);
			}

			~set()
			{}
	};
	
}

#endif