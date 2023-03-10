/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_set.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:27:43 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/10 21:00:19 by ldutriez         ###   ########.fr       */
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

			set operator&(const set & src) const
			{
				set result;
				
				for (auto & elem : *this)
					for (auto & elem2 : src)
						if (elem == elem2)
							result.push_back(elem);
				return (result);
			}

			set operator|(const set & src) const
			{
				set result(src);
				bool found(false);

				for (auto & elem : *this)
				{
					found = false;
					for (auto & elem2 : src)
						if (elem == elem2)
							found = true;
					if (!found)
						result.push_back(elem);
				}
				return (result);
			}

			set operator^(const set & src) const
			{
				set result;
				bool found(false);

				for (auto & elem : *this)
				{
					found = false;
					for (auto & elem2 : src)
						if (elem == elem2)
							found = true;
					if (!found)
						result.push_back(elem);
				}
				for (auto & elem : src)
				{
					found = false;
					for (auto & elem2 : *this)
						if (elem == elem2)
							found = true;
					if (!found)
						result.push_back(elem);
				}
				return (result);
			}
	};
}

#endif