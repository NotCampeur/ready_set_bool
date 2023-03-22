/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:06:44 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/23 00:52:43 by ldutriez         ###   ########.fr       */
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
	cout << "Enter a " B_CYAN "formula" NORMAL ": ";
	getline(cin, formula);
	return formula;
}

void exit_program(void)
{
	cout << B_WHITE "Bye!" NORMAL "\n";
	exit(EXIT_SUCCESS);
}

void seed_selection(void)
{
	string input;
	uint32_t seed(0);
	
	cout << B_CYAN "Enter a seed" NORMAL " if you want to use a specific seed,"
		<< " or " B_CYAN "just press enter" NORMAL " to use the current time as seed: ";
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
		uint32_t time_seed = time(NULL);
		srand(time_seed);
		std::cout << time_seed << "\n";
	}
	else
		srand(seed);
	cin.clear();
}

void bijective_test(void)
{
	std::cout << "Testing " B_WHITE "map" NORMAL " and " B_WHITE "reverse_map" NORMAL " equivalence:\n"
			<< "\tpress " B_CYAN "enter" NORMAL " to keep testing this module, " B_CYAN "n" NORMAL " to move to the next one\n";

	uint16_t x, y = 0;
	std::pair<uint16_t, uint16_t> result;
	
	auto get_spatial_data = [&](uint16_t &x, uint16_t &y) -> bool
	{
		std::cout << "Enter the x " B_CYAN "coordinate [0;" << std::numeric_limits<uint16_t>::max() << "]" NORMAL " : ";
		std::cin >> x;
		if (std::cin.eof() == true || std::cin.fail() == true)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << RED "Invalid coordinate" NORMAL "\n";
			return false;
		}
		std::cout << "Enter the y " B_CYAN "coordinate [0;" << std::numeric_limits<uint16_t>::max() << "]" NORMAL " : ";
		std::cin >> y;
		if (std::cin.eof() == true || std::cin.fail() == true)
		{
			std::cin.clear(); 
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << RED "Invalid coordinate" NORMAL "\n";
			return false;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return true;
	};

	auto tester = [&](void) -> void
	{
		if (get_spatial_data(x, y) == false)
			return;
		result = reverse_map(map(x, y));
		std::cout << "reverse_map(map(" << x << ", " << y << ")) = {"
			<< result.first << ", " << result.second << "}\n";
	};

	for (std::string input; input != "n" && std::cin.fail() == false;)
	{
		std::getline(std::cin, input);
		if (std::cin.fail() == false && input.empty() == true)
			tester();
		else if (input != "n" && std::cin.fail() == false)
			std::cout << RED "Invalid input" NORMAL "\n";
	}
}

void tests_index(void)
{
	unsigned long input(0);
	static vector<pair<string, void (*)(void)> > test_function = {
		make_pair("adder", adder_test),
		make_pair("multiplier", multiplier_test),
		make_pair("gray code", gray_code_test),
		make_pair("eval formula", eval_formula_test),
		make_pair("print truth table", print_truth_table_test),
		make_pair("NNF", negation_normal_form_test),
		make_pair("CNF", conjunctive_normal_form_test),
		make_pair("SAT", sat_test),
		make_pair("powerset", powerset_test),
		make_pair("eval set", eval_set_test),
		make_pair("map", map_test),
		make_pair("reverse_map", reverse_map_test),
		make_pair("bijective", bijective_test),
		make_pair("ast printer", ast_printer),
		make_pair("exit", exit_program)};

	while (cin.eof() == false)
	{
		cout << B_WHITE "Choose a module to test" NORMAL ":\n";
		for (unsigned long i(1); i < test_function.size() + 1; i++)
		{
			cout << GREEN << setw(2) << right << i - 1 << NORMAL ": ";
			if (i % 4 != 0)
				cout << setw(20) << left << test_function[i - 1].first;
			else if (i % 4 == 0)
				cout << test_function[i - 1].first << "\n";
			if (i == test_function.size())
				cout << "\n";
		}
		cin >> input;
		if (cin.fail() || input > test_function.size() - 1)
		{
			cout << RED "Invalid input" NORMAL "\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			((void (*)(void))test_function[input].second)();
		}
	}
	exit_program();
}

int main()
{
	cout << B_WHITE "Welcome in RSB!" NORMAL "\n\n";
	seed_selection();
	tests_index();
	return EXIT_FAILURE;
}