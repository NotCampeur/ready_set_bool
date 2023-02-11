/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_ast_node.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:16:08 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/11 16:17:07 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READY_SET_BOOL_RPN_AST_NODE_HPP
# define READY_SET_BOOL_RPN_AST_NODE_HPP

namespace rsb
{
	template <typename T>
	class node
	{
		public:
			node(const T & p_data) : data(p_data), left(nullptr), right(nullptr)
			{}
			
			node(const node<T> & to_copy)
			: data(to_copy.data)
			, left(to_copy.left->clone()), right(to_copy.right.clone())
			{}

			~node()
			{
				delete left;
				delete right;
			}

			node<T>	&operator=(const node<T> & to_assign)
			{
				if (this != &to_assign)
				{
					data = to_assign.data;
					left = to_assign.left.clone();
					right = to_assign.right.clone();
				}
				return *this;
			}

			// Return an allocated copy of the node and its children
			// Used for rpn_abstract_syntax_tree's deep copy
			node<T> *clone(void) const
			{
				node<T> *result(new node<T>(data));

				if (left != nullptr)
					result->left = left->clone();
				if (right != nullptr)
					result->right = right->clone();
				return result;
			}

			T			data;
			node<T>		*left;
			node<T>		*right;
	};
};

#endif