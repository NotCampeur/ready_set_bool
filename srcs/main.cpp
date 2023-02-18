/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:06:44 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/18 19:30:08 by ldutriez         ###   ########.fr       */
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

void tests_index(void)
{
	static void (*test_function[])(void) = {
		adder_test, multiplier_test,
		gray_code_test, ast_printer,
		eval_formula_test, print_truth_table_test,
		negation_normal_form_test};
	std::cout << "Choose a module to test:\n"
			<< "\t0: adder\n"
			<< "\t1: multiplier\n"
			<< "\t2: gray_code\n"
			<< "\t3: ast_printer\n"
			<< "\t4: eval_formula\n"
			<< "\t5: print_truth_table\n"
			<< "\t6: negation_normal_form\n"
			<< "\t7: exit\n";
	int input;
	std::cin >> input;
	if (std::cin.eof())
		return;
	if (std::cin.fail() || input < 0 || input > 7)
	{
		std::cout << "Invalid input\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		tests_index();
	}
	else if (input == 7)
		return;
	else
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		((void (*)(void))test_function[input])();
		tests_index();
	}
}

int main()
{
	std::cout << "Welcome in RSB!\n\n";
	seed_selection();
	tests_index();
	return EXIT_SUCCESS;
}