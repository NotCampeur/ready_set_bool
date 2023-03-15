/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_ast_checkers.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:14:42 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/15 16:03:34 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READY_SET_BOOL_RPN_AST_CHECKERS_HPP
# define READY_SET_BOOL_RPN_AST_CHECKERS_HPP

# include "math_set.hpp"

namespace rsb
{
	template <typename T, typename goal_type = char>
	class i_token_check
	{
		public:
			virtual bool is_same(const T & c, const goal_type & goal) const = 0;
			virtual bool is_operator(const T & c) const = 0;
			virtual bool is_value(const T & c) const = 0;
	};
	
	// Default token checker used by the abstract syntax tree
	// You can create your own token checker inheriting from i_token_check
	class token_check : public i_token_check<char>
	{
		public:
			bool is_same(const char & c, const char & goal) const
			{
				return (c == goal);
			}

			bool is_operator(const char & c) const
			{
				return (c == '+' || c == '-' || c == '*' || c == '/');
			}

			bool is_value(const char & c) const
			{
				return (c >= '0' && c <= '9');
			}
	};

	// Specialized token checker for boolean evaluation
	class boolean_token_check : public i_token_check<char>
	{
		public:
			bool is_same(const char & c, const char & goal) const
			{
				return (c == goal);
			}
			
			bool is_operator(const char & c) const
			{
				return (c == '!' || c == '&' || c == '|' ||
						c == '^' || c == '>' || c == '=');
			}

			bool is_value(const char & c) const
			{
				return (c == '0' || c == '1');
			}
	};

	// Specialized token checker for variable boolean formula
	// Mainly used to print truth tables and to normalize boolean formula
	class variable_boolean_token_check : public i_token_check<char>
	{
		public:
			bool is_same(const char & c, const char & goal) const
			{
				return (c == goal);
			}
			
			bool is_operator(const char & c) const
			{
				return (c == '!' || c == '&' || c == '|' ||
						c == '^' || c == '>' || c == '=');
			}
			
			bool is_value(const char & c) const
			{
				return ((c >= 'A' && c <= 'Z') || c == '0' || c == '1');
			}

			bool is_variable(const char & c) const
			{
				return (c >= 'A' && c <= 'Z');
			}
	};

	// Specialized token checker for logical evaluation of sets.
	class set_variable_boolean_token_check : public i_token_check<std::pair<char, rsb::set<__INT32_TYPE__> > >
	{
		public:
			bool is_same(const std::pair<char, rsb::set<__INT32_TYPE__> > & token, const char & goal) const
			{
				return (token.first == goal);
			}
			
			bool is_operator(const std::pair<char, rsb::set<__INT32_TYPE__> > & token) const
			{
				return (token.first == '!' || token.first == '&' || token.first == '|' ||
						token.first == '^' || token.first == '>' || token.first == '=');
			}

			bool is_value(const std::pair<char, rsb::set<__INT32_TYPE__> > & token) const
			{
				return ((token.first >= 'A' && token.first <= 'Z') ||
						token.first == '0' || token.first == '1');
			}
			bool is_variable(const std::pair<char, rsb::set<__INT32_TYPE__> > & token) const
			{
				return (token.first >= 'A' && token.first <= 'Z');
			}
	};
};

#endif