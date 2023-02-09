/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_abstract_syntax_tree.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:51:10 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/09 18:15:40 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACT_SYNTAX_TREE_HPP
# define ABSTRACT_SYNTAX_TREE_HPP

#include <vector>

namespace rsb
{
	// Default token checker used by the abstract syntax tree
	// You can create your own token checker by creating a class with two static functions:
	// static bool is_operator(const T & c)
	// static bool is_value(const T & c)
	// The first one should return true if the token is an operator
	// The second one should return true if the token is a value
	class token_check
	{
		public:
			static bool is_operator(const char & c)
			{
				return (c == '+' || c == '-' || c == '*' || c == '/');
			}

			static bool is_value(const char & c)
			{
				return (c >= '0' && c <= '9');
			}
	};

	// Specialized token checker for boolean evaluation
	class boolean_token_check
	{
		public:
			static bool is_operator(const char & c)
			{
				return (c == '!' || c == '&' || c == '|' ||
						c == '^' || c == '>' || c == '=');
			}

			static bool is_value(const char & c)
			{
				return (c == '0' || c == '1');
			}
	};

	template <typename T>
	class node
	{
		public:
			node(const T & p_data) : data(p_data), left(nullptr), right(nullptr)
			{}
			
			node(const node<T> & to_copy)
			: data(to_copy.data)
			, left(to_copy.left), right(to_copy.right)
			{}

			~node()
			{
				delete left;
				delete right;
			}

			node<T>		&operator=(const node<T> & to_assign)
			{
				if (this != &to_assign)
				{
					data = to_assign.data;
					left = to_assign.left;
					right = to_assign.right;
				}
				return *this;
			}

			T			data;
			node<T>		*left;
			node<T>		*right;
	};

	// Implementation of a Reverse Polish Notation Abstract Syntax Tree
	// The tree is built from a vector of tokens
	// You can set a token_checker class to check if T is an operator or a value
	template <
		class T,
		class token_checker = rsb::token_check
	> class rpn_abstract_syntax_tree
	{
		public:
			rpn_abstract_syntax_tree() : _root(nullptr)
			{}

			rpn_abstract_syntax_tree(const rpn_abstract_syntax_tree<T> & to_copy)
			: _root(to_copy._root)
			{}

			rpn_abstract_syntax_tree(const std::vector<T> & tokens)
			: _root(nullptr)
			{
				build(tokens);
			}

			~rpn_abstract_syntax_tree()
			{
				delete _root;
			}

			rpn_abstract_syntax_tree<T>		&operator=(const rpn_abstract_syntax_tree<T> & to_assign)
			{
				if (this != &to_assign)
				{
					if (_root != nullptr)
						delete _root;
					if (to_assign._root != nullptr)
						_root = new node<T>(*(to_assign._root));
				}
				return *this;
			}

			// Build the tree from a vector of tokens
			// The vector should be in Reverse Polish Notation
			// Throws on invalid token
			void build(const std::vector<T> & tokens)
			{
				std::vector<node<T> *>	stack;

				for (const T & token : tokens)
				{
					if (token_checker::is_value(token))
					{
						stack.push_back(new node<T>(token));
					}
					else if (token_checker::is_operator(token))
					{
						node<T>		*right = stack.back();
						stack.pop_back();
						node<T>		*left = stack.back();
						stack.pop_back();
						node<T>		*new_node = new node<T>(token);
						new_node->left = left;
						new_node->right = right;
						stack.push_back(new_node);
					}
					else
					{
						throw std::invalid_argument("Invalid token");
					}
				}
				_root = stack.back();
				stack.pop_back();
			}

			void print()
			{
				_print(_root);
			}


		private:
			void _print(node<T> * n)
			{
				static int	indent = 0;
				if (n == nullptr)
					return ;
				++indent;
				_print(n->left);
				for (int i = 0; i < indent; i++)
					std::cout << "--";
				std::cout << n->data << std::endl;
				_print(n->right);
				--indent;
			}
			
			node<T>			*_root;
	};

};

#endif