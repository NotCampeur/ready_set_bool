/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:06:44 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/18 17:49:35 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"

std::string get_formula(void)
{
	std::string formula;
	std::cout << "Enter a formula: ";
	std::getline(std::cin, formula);
	return formula;
}

void seed_selection(void)
{
	std::string input;
	__UINT32_TYPE__ seed(0);
	
	std::cout << "Enter a seed if you want to use a specific seed, or just press enter to use the current time as seed: ";
	std::getline(std::cin, input);
	try
	{
		seed = std::stoul(input);
	}
	catch(...)
	{
		input.clear();
	}
	
	if (std::cin.fail() || input.empty() || input == "\n")
		srand(time(NULL));
	else
		srand(seed);
	std::cin.clear();
}

int main()
{
	std::cout << "Welcome in RSB!\n\n";
	seed_selection();
	adder_test();
	multiplier_test();
	gray_code_test();
	ast_printer();
	eval_formula_test();
	print_truth_table_test();
	negation_normal_form_test();
	return EXIT_SUCCESS;
}