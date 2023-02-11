/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_ast_checkers.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:14:42 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/11 16:15:34 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READY_SET_BOOL_RPN_AST_CHECKERS_HPP
# define READY_SET_BOOL_RPN_AST_CHECKERS_HPP

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

	// Specialized token checker for variable boolean formula
	// Mainly used to print truth tables and to normalize boolean formula
	class variable_boolean_token_check : public boolean_token_check
	{
		public:
			static bool is_value(const char & c)
			{
				return ((c >= 'A' && c <= 'Z') || boolean_token_check::is_value(c));
			}
	};
};

#endif