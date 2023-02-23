/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_abstract_syntax_tree.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:51:10 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/23 14:06:53 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACT_SYNTAX_TREE_HPP
# define ABSTRACT_SYNTAX_TREE_HPP

#include <vector>
#include <map> //? Use in print_truth_table
#include <algorithm> //? Use in print_truth_table for std::replace
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
			rpn_abstract_syntax_tree() : _root(nullptr), _checker()
			{}

			rpn_abstract_syntax_tree(const rpn_abstract_syntax_tree<T, token_checker> & to_copy)
			: _root(to_copy._root->clone()), _checker()
			{}

			rpn_abstract_syntax_tree(node<T> * node)
			: _root(node->clone()), _checker()
			{}

			rpn_abstract_syntax_tree(const std::vector<T> & tokens)
			: _root(nullptr), _checker()
			{
				if (tokens.size() > 0)
					build(tokens);
			}

			~rpn_abstract_syntax_tree()
			{
				delete _root;
			}

			rpn_abstract_syntax_tree<T, token_checker> &
			operator=(const rpn_abstract_syntax_tree<T, token_checker> & to_assign)
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
				{
					delete _root;
					_root = nullptr;
				}
				if (tokens.size() == 0)
					return;
				for (const T & token : tokens)
				{
					if (_checker.is_value(token) == true)
					{
						stack.push_back(new node<T>(token));
					}
					else if (_checker.is_operator(token) == true)
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
							new_node->left->parent = new_node;
							stack.push_back(new_node);
							continue;
						}
						node<T>		*right = stack.back();
						stack.pop_back();
						node<T>		*left = stack.back();
						stack.pop_back();
						node<T>		*new_node = new node<T>(token);
						new_node->left = left;
						new_node->left->parent = new_node;
						new_node->right = right;
						new_node->right->parent = new_node;
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

			std::string formula(void) const
			{
				std::string result;

				if (_root != nullptr)
					result = _root->formula();
				return result;
			}

			// Print the truth table of the boolean formula
			// throw std::runtime_error if the tree is empty or malformed
			// throw std::runtime_error if the token checker is not a variable_boolean_token_check
			void print_truth_table(void) const
			{
				if (std::is_same<token_checker, rsb::variable_boolean_token_check>::value == false)
					throw std::runtime_error("Wrong token checker");
				if (_root == nullptr)
					return;

				rsb::rpn_abstract_syntax_tree<T, rsb::boolean_token_check> evaluation_tree;
				std::map<char, bool> variables;
				bool result(false);
				size_t max_variations(0);
				std::string current_formula(formula());
				std::string formula_variation;
				
				for (char var : current_formula)
					if (_checker.is_variable(var) == true)
						variables[var] = false;
				_print_truth_table_header(variables);
				max_variations = 1 << variables.size();
				for (size_t i(0); i < max_variations; ++i)
				{
					formula_variation = current_formula;
					for (typename std::map<char, bool>::iterator it(variables.begin());
						it != variables.end(); ++it)
					{
						it->second = (i & (1 << (std::distance(it, variables.end()) - 1))) != 0;
						std::cout << "| " << it->second << " ";
						std::replace(formula_variation.begin(), formula_variation.end(),
							it->first, it->second == true ? '1' : '0');
					}
					try
					{
						evaluation_tree.build(std::vector<char>(formula_variation.begin(), formula_variation.end()));
					}
					catch(const std::exception& e)
					{
						std::cerr << e.what() << '\n';
						return;
					}
					result = evaluation_tree.evaluate();
					std::cout << "| " << result << " |\n";
				}
			}

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
				if (_checker.is_value(_root->data) == true)
					return (_root->data == '1');
				else if (_checker.is_operator(_root->data) == true)
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

			// Format the tree to only have !, & and | operators and simplify negation.
			// AB&! => A!B!|
			void negation_normal_form(void)
			{
				if (_root == nullptr)
					return;
				_negation_normal_form(_root);
			}

			void print()
			{
				_print(_root);
			}

		private:

			void _negation_normal_form(node<T> * n)
			{
				if (n == nullptr)
					return ;
				if (n->data == '!')
				{
					if (n->left->data == '!')
					{
						node<T> *tmp(n->left->left);
						n->left->left = nullptr;
						if (_root == n)
							_root = tmp;
						else if (n->parent->left == n)
							n->parent->left = tmp;
						else if (n->parent->right == n)
							n->parent->right = tmp;
						delete n;
						n = tmp;
					}
					else if (n->left->data == '&' || n->left->data == '|')
					{
						n->data = (n->left->data == '&') ? '|' : '&';
						n->left->data = '!';
						n->right = new node<T>('!');
						n->right->left = n->left->right;
						n->right->left->parent = n->right;
						n->left->right = nullptr;
					}
					else if (n->left->data == '>')
					{
						n->left->data = '&';
						n->left->parent = n->parent;
						if (_root == n)
							_root = n->left;
						else if (n->parent->left == n)
							n->parent->left = n->left;
						else if (n->parent->right == n)
							n->parent->right = n->left;
						n->parent = n->left;
						n->left = n->left->right;
						n->left->parent = n;
						n->parent->right = n;
						n = n->parent;
					}
				}
				else if (n->data == '>')
				{
					n->data = '|';
					n->left->parent = new node<T>('!');
					n->left->parent->left = n->left;
					n->left = n->left->parent;
					n->left->parent = n;
				}
				else if (n->data == '=')
				{
					node<T> *new_parent(new node<T>('|'));
					
					n->data = '&';
					if (_root == n)
						_root = new_parent;
					else if (n->parent->left == n)
						n->parent->left = new_parent;
					else if (n->parent->right == n)
						n->parent->right = new_parent;
					new_parent->parent = n->parent;
					new_parent->left = n;
					n->parent = new_parent;
					
					new_parent->right = new node<T>('&');
					new_parent->right->parent = new_parent;

					new_parent->right->left = new node<T>('!');
					new_parent->right->left->parent = new_parent->right;
					new_parent->right->left->left = new node<T>(n->left->data);
					new_parent->right->left->left->parent = new_parent->right->left;

					new_parent->right->right = new node<T>('!');
					new_parent->right->right->parent = new_parent->right;
					new_parent->right->right->left = new node<T>(n->right->data);
					new_parent->right->right->left->parent = new_parent->right->right;

					n = new_parent;
				}
				_negation_normal_form(n->left);
				_negation_normal_form(n->right);
			}

			void _print_truth_table_header(const std::map<T, bool> &variables) const
			{
				for (std::pair<T, bool> pair : variables)
					std::cout << "| " << pair.first << " ";
				std::cout << "| = |\n";
				for (typename std::map<T, bool>::size_type i(0); i < variables.size(); i++)
					std::cout << "|---";
				std::cout << "|---|\n";
			}
			
			void _print(node<T> * n)
			{
				static int	indent = -1;
				if (n == nullptr)
					return ;
				++indent;
				_print(n->left);
				for (int i = 0; i < indent - 1; i++)
					std::cout << "  ";
				if (indent > 0)
					std::cout << "--";
				std::cout << n->data << std::endl;
				_print(n->right);
				--indent;
			}
			
			node<T>			*_root;
			token_checker	_checker;
	};
};

#endif