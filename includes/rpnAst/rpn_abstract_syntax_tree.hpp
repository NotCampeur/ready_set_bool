/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_abstract_syntax_tree.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:51:10 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/15 17:23:17 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACT_SYNTAX_TREE_HPP
# define ABSTRACT_SYNTAX_TREE_HPP

#include <vector>
#include <map> //? Use in print_truth_table
#include <algorithm> //? Use in print_truth_table for std::replace
#include "rpn_ast_checkers.hpp"
#include "rpn_ast_node.hpp"
#include "math_set.hpp"

namespace rsb
{
	// Implementation of a Reverse Polish Notation Abstract Syntax Tree
	// The tree is built from a vector of tokens
	// You can set a token_checker class to check if T is an operator or a value
	template <
		class T,
		class token_checker = rsb::i_token_check<T>
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
						if ((stack.size() < 2 && _checker.is_same(token, '!') == false) ||
							(stack.size() < 1 && _checker.is_same(token, '!') == true))
						{
							for (node<T> * node : stack)
								delete node;
							throw std::invalid_argument("Invalid formula");
						}
						if (_checker.is_same(token, '!') == true && stack.size() > 0)
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

			bool is_satisfiable(void)
			{
				if (std::is_same<token_checker, rsb::variable_boolean_token_check>::value == false)
					throw std::runtime_error("Wrong token checker");
				if (_root == nullptr)
					return false;

				rsb::rpn_abstract_syntax_tree<T, rsb::boolean_token_check> evaluation_tree;
				std::map<char, bool> variables;
				bool result(false);
				size_t max_variations(0);
				std::string current_formula(formula());
				std::string formula_variation;
				
				for (char var : current_formula)
					if (_checker.is_variable(var) == true)
						variables[var] = false;
				max_variations = 1 << variables.size();
				for (size_t i(0); i < max_variations; ++i)
				{
					formula_variation = current_formula;
					for (typename std::map<char, bool>::iterator it(variables.begin());
						it != variables.end(); ++it)
					{
						it->second = (i & (1 << (std::distance(it, variables.end()) - 1))) != 0;
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
						return false;
					}
					result = evaluation_tree.evaluate();
					if (result == true)
						return true;
				}
				return false;
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

			// An evaluate specialization for set_variable_boolean_token_check
			// Used to evaluate a formula on sets.
			// throw std::runtime_error if the tree is empty or malformed
			// throw std::runtime_error if the token checker is not a set_variable_boolean_token_check
			// throw std::runtime_error if T is not a pair
			rsb::set<int32_t> set_evaluate(const rsb::set<int32_t> & encompassing_set) const
			{
				rsb::set<int32_t> result;

				if (std::is_same<token_checker, rsb::set_variable_boolean_token_check>::value == false)
					throw std::runtime_error("Wrong token checker");
				if (std::is_same<T, std::pair<char, rsb::set<int32_t>>>::value == false)
					throw std::runtime_error("Wrong type");
				if (_root == nullptr)
					throw std::runtime_error("Empty or malformed tree");
				if (_checker.is_value(_root->data) == true)
				{
					return rsb::set<int32_t>(_root->data.second);
				}
				else if (_checker.is_operator(_root->data) == true)
				{
					rsb::set<int32_t> left(rpn_abstract_syntax_tree(_root->left).set_evaluate(encompassing_set));
					rsb::set<int32_t> right;

					if (_checker.is_same(_root->data, '!') == false)
						right = rpn_abstract_syntax_tree(_root->right).set_evaluate(encompassing_set);
					if (_checker.is_same(_root->data, '!') == true)
						result = encompassing_set ^ left;
					else if (_checker.is_same(_root->data, '&') == true)
						result = left & right;
					else if (_checker.is_same(_root->data, '|') == true)
						result = left | right;
					else if (_checker.is_same(_root->data, '^') == true)
						result = left ^ right;
					else if (_checker.is_same(_root->data, '>') == true) //!Not sure
						result = encompassing_set ^ (left & (encompassing_set ^ right));
					else if (_checker.is_same(_root->data, '=') == true)
						result = (left & right) |
							((encompassing_set ^ (left)) &
							(encompassing_set ^ (right)));
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

			// Format the tree to only have !, & and | operators,
			// simplify negation and distribute conjunction and disjunction.
			// AB&!C!| => A!B!|C!| => A!B!C!||
			void conjunctive_normal_form(void)
			{
				if (_root == nullptr)
					return;
				_negation_normal_form(_root);
				_conjunctive_normal_form(_root);
			}

			void print()
			{
				_print(_root);
			}

		private:

			void _conjunctive_normal_form(node<T> *n)
			{
				if (n == nullptr)
					return;
				if ((n->data == '|' || n->data == '&')
					&& n->left->data == n->data)
				{
					node<T> *tmp(n->left->right);
					n->left->right = nullptr;
					tmp->parent = n;
					n->left->parent = n->parent;
					if (_root == n)
						_root = n->left;
					else if (n->parent->left == n)
						n->parent->left = n->left;
					else if (n->parent->right == n)
						n->parent->right = n->left;
					n->parent = n->left;
					n->left->right = n;
					n->left = tmp;
					tmp->parent = n;
					n = n->parent;
					_conjunctive_normal_form(_root);
				}
				else if (n->data == '|' && n->left->data == '&')
				{
					node<T> *tmp(n->left->right);
					n->left->right = nullptr;
					n->left->parent = n->parent;
					if (_root == n)
						_root = n->left;
					else if (n->parent->left == n)
						n->parent->left = n->left;
					else if (n->parent->right == n)
						n->parent->right = n->left;
					n->parent = n->left;
					n->left->right = n;
					n->left = tmp;
					tmp->parent = n;
					n = n->parent;
					tmp = n->left;
					n->left = new node<T>('|');
					n->left->parent = n;
					n->left->left = tmp;
					tmp->parent = n->left;
					n->left->right = n->right->right->clone();
					n->left->right->parent = n->left;
					_conjunctive_normal_form(_root);
				}
				else if (n->data == '|' && n->right->data == '&')
				{
					node<T> *tmp(n->right->left);

					n->right->left = nullptr;
					n->right->parent = n->parent;
					if (_root == n)
						_root = n->right;
					else if (n->parent->left == n)
						n->parent->left = n->right;
					else if (n->parent->right == n)
						n->parent->right = n->right;
					n->parent = n->right;
					n->right->left = n;
					n->right = tmp;
					tmp->parent = n;
					n = n->parent;
					tmp = n->right;
					n->right = new node<T>('|');
					n->right->parent = n;
					n->right->right = tmp;
					tmp->parent = n->right;
					n->right->left = n->left->left->clone();
					n->right->left->parent = n->right;
					_conjunctive_normal_form(_root);
				}
				_conjunctive_normal_form(n->left);
				_conjunctive_normal_form(n->right);
			}

			int _nnf_negation_case(node<T> ** n)
			{
				if ((*n)->left->data == '!')
				{
					node<T> *tmp((*n)->left->left);
					(*n)->left->left = nullptr;
					tmp->parent = (*n)->parent;
					if (_root == *n)
						_root = tmp;
					else if ((*n)->parent->left == *n)
						(*n)->parent->left = tmp;
					else if ((*n)->parent->right == *n)
						(*n)->parent->right = tmp;
					delete *n;
					*n = tmp;
				}
				else if ((*n)->left->data == '&' || (*n)->left->data == '|')
				{
					(*n)->data = ((*n)->left->data == '&') ? '|' : '&';
					(*n)->left->data = '!';
					(*n)->right = new node<T>('!');
					(*n)->right->parent = *n;
					(*n)->right->left = (*n)->left->right;
					(*n)->right->left->parent = (*n)->right;
					(*n)->left->right = nullptr;
				}
				else if ((*n)->left->data == '>' || (*n)->left->data == '=' ||
						(*n)->left->data == '^')
				{
					_negation_normal_form((*n)->left);
					_negation_normal_form(*n);
					return 1;
				}
				return 0;
			}

			void _nnf_material_condition_case(node<T> * n)
			{
				n->data = '|';
				n->left->parent = new node<T>('!');
				n->left->parent->left = n->left;
				n->left = n->left->parent;
				n->left->parent = n;
			}

			void _nnf_equivalence_case(node<T> ** n)
			{
				node<T> *new_parent(new node<T>('|'));
				
				(*n)->data = '&';
				if (_root == *n)
					_root = new_parent;
				else if ((*n)->parent->left == *n)
					(*n)->parent->left = new_parent;
				else if ((*n)->parent->right == *n)
					(*n)->parent->right = new_parent;
				new_parent->parent = (*n)->parent;
				new_parent->left = *n;
				(*n)->parent = new_parent;
				
				new_parent->right = new node<T>('&');
				new_parent->right->parent = new_parent;

				new_parent->right->left = new node<T>('!');
				new_parent->right->left->parent = new_parent->right;
				new_parent->right->left->left = (*n)->left->clone();
				new_parent->right->left->left->parent = new_parent->right->left;

				new_parent->right->right = new node<T>('!');
				new_parent->right->right->parent = new_parent->right;
				new_parent->right->right->left = (*n)->right->clone();
				new_parent->right->right->left->parent = new_parent->right->right;

				*n = new_parent;
			}

			void _nnf_exclusive_disjunction_case(node<T> * n)
			{
				n->data = '!';
				n->left->parent = new node<T>('=');
				n->left->parent->left = n->left;
				n->left = n->left->parent;
				n->left->parent = n;
				n->left->right = n->right;
				n->right->parent = n->left;
				n->right = nullptr;
				_negation_normal_form(n);
			}

			void _negation_normal_form(node<T> * n)
			{
				if (n == nullptr)
					return ;
				switch (n->data)
				{
					case '!':
						if (_nnf_negation_case(&n) == 1)
							return ;
						break;
					case '>':
						_nnf_material_condition_case(n);
						break;
					case '=':
						_nnf_equivalence_case(&n);
						break;
					case '^':
						_nnf_exclusive_disjunction_case(n);
						return;
					default:
						break;
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
				_print(n->right);
				for (int i = 0; i < indent - 1; i++)
					std::cout << "  ";
				if (indent > 0)
					std::cout << "--";
				std::cout << n->data << std::endl;
				_print(n->left);
				--indent;
			}
			
			node<T>			*_root;
			token_checker	_checker;
	};
};

template<typename U, typename V>
std::ostream &operator<<(std::ostream &os, const std::pair<U, V> &pair)
{
	os << pair.first;
	return os;
}

#endif