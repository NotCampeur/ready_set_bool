/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ready_set_bool.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:56:02 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/23 17:18:34 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READY_SET_BOOL_HPP
# define READY_SET_BOOL_HPP

# include <iostream>
# include <cstdint>
# include <vector>
# include <limits>
# include "math_set.hpp"

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define B_GREEN "\033[1;32m"
# define U_GREEN "\033[4;32m"
# define YELLOW "\033[0;33m"
# define B_YELLOW "\033[1;33m"
# define BLUE "\033[0;34m"
# define B_BLUE "\033[1;34m"
# define PURPLE "\033[0;35m"
# define B_PURPLE "\033[1;35m"
# define U_WHITE "\033[4;37m"
# define B_WHITE "\033[1;37m"
# define B_CYAN "\033[1;36m"
# define NORMAL "\033[0m"

// ALGEBRA FUNCTIONS

uint32_t adder(uint32_t a, uint32_t b);
uint32_t multiplier(uint32_t a, uint32_t b);
uint32_t gray_code(uint32_t n);
bool eval_formula(const std::string &formula);
void print_truth_table(const std::string &formula);
std::string negation_normal_form(const std::string &formula);
std::string conjunctive_normal_form(const std::string &formula);
bool sat(const std::string & formula);
rsb::set<rsb::set<int32_t> > powerset(rsb::set<int32_t> set);
rsb::set<int32_t> eval_set(const std::string &formula,
								const rsb::set<rsb::set<int32_t> > &sets);
double map(uint16_t x, uint16_t y);
std::pair<uint16_t, uint16_t> reverse_map(double data);

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
void eval_set_test(void);
void map_test(void);
void reverse_map_test(void);
void bijective_test(void);
void complete_test(void);

#endif