/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_abstract_syntax_tree.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:51:10 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/11 16:18:04 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACT_SYNTAX_TREE_HPP
# define ABSTRACT_SYNTAX_TREE_HPP

#include <vector>
#include "rpn_ast_checkers.hpp"
#include "rpn_ast_node.hpp"

namespace rsb
{
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
					bool right(false);
					
					if (_root->data != '!')
						right = rpn_abstract_syntax_tree(_root->right).evaluate();

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
			// If the tree is already built, it will be deleted and rebuilt
			void build(const std::vector<T> & tokens)
			{
				std::vector<node<T> *>	stack;

				if (_root != nullptr)
					delete _root;
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
				if (stack.size() != 0)
				{
					for (node<T> * node : stack)
						delete node;
					throw std::invalid_argument("Invalid formula, missing operator");
				}
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