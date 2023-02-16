/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_ast_checkers.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:14:42 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/16 14:32:17 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READY_SET_BOOL_RPN_AST_CHECKERS_HPP
# define READY_SET_BOOL_RPN_AST_CHECKERS_HPP

namespace rsb
{
	class i_token_check
	{
		public:
			virtual bool is_operator(const char & c) const = 0;
			virtual bool is_value(const char & c) const = 0;
	};
	
	// Default token checker used by the abstract syntax tree
	// You can create your own token checker inheriting from i_token_check
	class token_check : public i_token_check
	{
		public:
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
	class boolean_token_check : public i_token_check
	{
		public:
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
	class variable_boolean_token_check : public boolean_token_check
	{
		public:
			bool is_value(const char & c) const
			{
				return ((c >= 'A' && c <= 'Z') || boolean_token_check::is_value(c));
			}
			bool is_variable(const char & c) const
			{
				return (c >= 'A' && c <= 'Z');
			}
	};
};

#endif