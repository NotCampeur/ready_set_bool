/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ready_set_bool.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:56:02 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/06 19:07:56 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READY_SET_BOOL_HPP
# define READY_SET_BOOL_HPP

# include <iostream>
# include <vector>
# include <limits>

// ALGEBRA FUNCTIONS

__UINT32_TYPE__ adder(__UINT32_TYPE__ a, __UINT32_TYPE__ b);
__UINT32_TYPE__ multiplier(__UINT32_TYPE__ a, __UINT32_TYPE__ b);
__UINT32_TYPE__ gray_code(__UINT32_TYPE__ n);
bool eval_formula(const std::string &formula);
void print_truth_table(const std::string &formula);
std::string negation_normal_form(const std::string &formula);
std::string conjunctive_normal_form(const std::string &formula);
bool sat(std::string & formula);
std::vector<std::vector<__INT32_TYPE__> > powerset(std::vector<__INT32_TYPE__> set);

// TESTING FUNCTIONS

std::string get_formula(void);
void adder_test(void);
void multiplier_test(void);
void gray_code_test(void);
void ast_printer(void);
void eval_formula_test(void);
void print_truth_table_test(void);
void negation_normal_form_test(void);
void conjunctive_normal_form_test(void);
void sat_test(void);
void powerset_test(void);

#endif