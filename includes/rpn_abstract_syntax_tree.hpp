/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_abstract_syntax_tree.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:51:10 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/09 21:15:56 by ldutriez         ###   ########.fr       */
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

	// Implementation of a Reverse Polish Notation Abstract Syntax Tree
	// The tree is built from a vector of tokens
	// You can set a token_checker class to check if T is an operator or a value
	template <
		class T,
		class token_checker = rsb::token_check
	> class rpn_abstract_syntax_tree
	{
		public:

			// A boolean evaluator function
			// You can use it to evaluate a boolean expression
			// throw std::runtime_error if the tree is empty or malformed
			// throw std::runtime_error if the token checker is not a boolean_token_check
			bool evaluate(void) const
			{
				bool result(false);
				
				if (std::is_same<token_checker, rsb::boolean_token_check>::value == false)
					throw std::runtime_error("Wrong token checker");
				if (_root == nullptr)
					throw std::runtime_error("Empty or malformed tree");
				if (token_checker::is_value(_root->data))
					return (_root->data == '1');
				else if (token_checker::is_operator(_root->data))
				{
					bool left(rpn_abstract_syntax_tree(_root->left).evaluate());
					bool right;
					
					if (_root->data != '!')
						right = rpn_abstract_syntax_tree(_root->right).evaluate();

					std::cout << std::boolalpha << left << " " << _root->data << " " << right << std::endl;
					if (_root->data == '!')
						result = !left;
					else if (_root->data == '&')
						result = left && right;
					else if (_root->data == '|')
						result = left || right;
					else if (_root->data == '^')
						result = left ^ right;
					else if (_root->data == '>')
						result = !(left && !right);
					else if (_root->data == '=')
						result = left == right;
				}
				return result;
			}

			rpn_abstract_syntax_tree() : _root(nullptr)
			{}

			rpn_abstract_syntax_tree(const rpn_abstract_syntax_tree<T> & to_copy)
			: _root(to_copy._root->clone())
			{}

			rpn_abstract_syntax_tree(node<T> * node)
			: _root(node->clone())
			{}

			rpn_abstract_syntax_tree(const std::vector<T> & tokens)
			: _root(nullptr)
			{
				if (tokens.size() > 0)
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
					_root = to_assign._root->clone();
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
						if ((stack.size() < 2 && token != '!') ||
							(stack.size() < 1 && token == '!'))
						{
							for (node<T> * node : stack)
								delete node;
							throw std::invalid_argument("Invalid formula");
						}
						if (token == '!' && stack.size() > 0)
						{
							node<T>		*left = stack.back();
							stack.pop_back();
							node<T>		*new_node = new node<T>(token);
							new_node->left = left;
							stack.push_back(new_node);
							continue;
						}
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
						for (node<T> * node : stack)
							delete node;
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