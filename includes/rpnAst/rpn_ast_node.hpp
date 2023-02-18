/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_ast_node.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:16:08 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/18 17:18:22 by ldutriez         ###   ########.fr       */
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
			node(const T & p_data) : data(p_data), parent(nullptr), left(nullptr), right(nullptr)
			{}
			
			node(const node<T> & to_copy)
			: data(to_copy.data), parent(nullptr)
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
					parent = nullptr;
					left = to_assign.left.clone();
					right = to_assign.right.clone();
				}
				return *this;
			}

			// Return a string representation of the node and its children
			// Used to build a formula from the tree
			// Parents are ignored.
			std::string formula(void) const
			{
				std::string result;

				if (left != nullptr)
					result += left->formula();
				if (right != nullptr)
					result += right->formula();
				result += data;
				return result;
			}

			// Return an allocated copy of the node and its children
			// Used for rpn_abstract_syntax_tree's deep copy
			// To avoid clunky behavior, the node from which the copy is made
			// is considered the root of the new tree and its parent is not set.
			node<T> *clone(void) const
			{
				node<T> *result(new node<T>(data));

				if (left != nullptr)
				{
					result->left = left->clone();
					result->left->parent = result;
				}
				if (right != nullptr)
				{
					result->right = right->clone();
					result->right->parent = result;
				}
				return result;
			}

			T			data;
			node<T>		*parent;
			node<T>		*left;
			node<T>		*right;
	};
};

#endif