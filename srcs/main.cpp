/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:06:44 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/06 19:05:58 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"
#include <vector>
#include <utility>
#include <iomanip>

using namespace std;

string get_formula(void)
{
	string formula;
	cout << "Enter a \033[1;36mformula\033[0m: ";
	getline(cin, formula);
	return formula;
}

void exit_program(void)
{
	cout << "\033[1;37mBye!\033[0m\n";
	exit(EXIT_SUCCESS);
}

void seed_selection(void)
{
	string input;
	__UINT32_TYPE__ seed(0);
	
	cout << "\033[1;36mEnter a seed\033[0m if you want to use a specific seed,"
		<< " or \033[1;36mjust press enter\033[0m to use the current time as seed: ";
	getline(cin, input);
	try
	{
		seed = stoul(input);
	}
	catch(...)
	{
		input.clear();
	}
	
	if (cin.fail() || input.empty() || input == "\n")
	{
		__UINT32_TYPE__ time_seed = time(NULL);
		srand(time_seed);
		std::cout << time_seed << "\n";
	}
	else
		srand(seed);
	cin.clear();
}

void tests_index(void)
{
	static vector<pair<string, void (*)(void)> > test_function = {
		make_pair("adder", adder_test),
		make_pair("multiplier", multiplier_test),
		make_pair("gray code", gray_code_test),
		make_pair("ast printer", ast_printer),
		make_pair("eval formula", eval_formula_test),
		make_pair("print truth table", print_truth_table_test),
		make_pair("NNF", negation_normal_form_test),
		make_pair("CNF", conjunctive_normal_form_test),
		make_pair("SAT", sat_test),
		make_pair("powerset", powerset_test),
		make_pair("exit", exit_program)};

	cout << "Choose a module to test:\n";
	for (unsigned long i(1); i < test_function.size() + 1; i++)
	{
		if ((i - 1) % 4 != 0)
			cout << '\t';
		cout << "\033[4;32m" << i - 1 << "\033[0m: " << test_function[i - 1].first;
		if (i % 4 == 0 || i == test_function.size())
			std::cout << "\n";
	}
	unsigned long input(0);
	cin >> input;
	if (cin.eof())
		return;
	if (cin.fail() || input > test_function.size() - 1)
	{
		cout << "\033[0;31mInvalid input\033[0m\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		tests_index();
	}
	else
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		((void (*)(void))test_function[input].second)();
		tests_index();
	}
}

int main()
{
	cout << "\033[1;37mWelcome in RSB!\033[0m\n\n";
	seed_selection();
	tests_index();
	return EXIT_FAILURE;
}