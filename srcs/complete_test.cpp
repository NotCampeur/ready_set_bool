/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_test.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 01:35:51 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/23 16:17:53 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_set_bool.hpp"

void complete_test(void)
{
	std::cout << "Testing " B_WHITE "every" NORMAL " functions:\n";

	{
		std::cout << "\t" B_WHITE "adder" NORMAL ":\n";
		std::cout << "adder(0, 0) = " << adder(0, 0) << "\n";
		std::cout << "adder(1, 0) = " << adder(1, 0) << "\n";
		std::cout << "adder(0, 1) = " << adder(0, 1) << "\n";
		std::cout << "adder(1, 1) = " << adder(1, 1) << "\n";
		std::cout << "adder(1, 2) = " << adder(1, 2) << "\n";
		std::cout << "adder(2, 2) = " << adder(2, 2) << "\n";
	}
	{
		std::cout << "\t" B_WHITE "multiplier" NORMAL ":\n";
		std::cout << "multiplier(0, 0) = " << multiplier(0, 0) << "\n";
		std::cout << "multiplier(1, 0) = " << multiplier(1, 0) << "\n";
		std::cout << "multiplier(0, 1) = " << multiplier(0, 1) << "\n";
		std::cout << "multiplier(1, 1) = " << multiplier(1, 1) << "\n";
		std::cout << "multiplier(1, 2) = " << multiplier(1, 2) << "\n";
		std::cout << "multiplier(2, 2) = " << multiplier(2, 2) << "\n";
	}
	{
		std::cout << "\t" B_WHITE "boolean evaluation" NORMAL ":\n";
		std::cout << std::boolalpha;
		std::cout << U_WHITE "Basic tests\n" NORMAL;
		std::cout << "0! = " << eval_formula("0!") << "\n";
		std::cout << "1! = " << eval_formula("1!") << "\n";
		std::cout << "00| = " << eval_formula("00|") << "\n";
		std::cout << "10| = " << eval_formula("10|") << "\n";
		std::cout << "01| = " << eval_formula("01|") << "\n";
		std::cout << "11| = " << eval_formula("11|") << "\n";
		std::cout << "10& = " << eval_formula("10&") << "\n";
		std::cout << "11& = " << eval_formula("11&") << "\n";
		std::cout << "11^ = " << eval_formula("11^") << "\n";
		std::cout << "10^ = " << eval_formula("10^") << "\n";
		std::cout << "00> = " << eval_formula("00>") << "\n";
		std::cout << "01> = " << eval_formula("01>") << "\n";
		std::cout << "10> = " << eval_formula("10>") << "\n";
		std::cout << "11> = " << eval_formula("11>") << "\n";
		std::cout << "00= = " << eval_formula("00=") << "\n";
		std::cout << "11= = " << eval_formula("11=") << "\n";
		std::cout << "10= = " << eval_formula("10=") << "\n";
		std::cout << "01= = " << eval_formula("01=") << "\n";
		std::cout << U_WHITE "Composition\n" NORMAL;
		std::cout << "11&0| = " << eval_formula("11&0|") << "\n";
		std::cout << "10&1| = " << eval_formula("10&1|") << "\n";
		std::cout << "11&1| = " << eval_formula("11&1|") << "\n";
		std::cout << "11&1|1^ = " << eval_formula("11&1|1^") << "\n";
		std::cout << "01&1|1= = " << eval_formula("01&1|1=") << "\n";
		std::cout << "01&1&1& = " << eval_formula("01&1&1&") << "\n";
		std::cout << "0111&&& = " << eval_formula("0111&&&") << "\n";
		std::cout << std::noboolalpha;
	}
	{
		std::cout << "\t" B_WHITE "truth table" NORMAL ":\n";
		std::cout << U_WHITE "Basic tests\n" NORMAL;
		std::cout << "Formula: A\n";
		print_truth_table("A");
		std::cout << "Formula: A!\n";
		print_truth_table("A!");
		std::cout << "Formula: AB|\n";
		print_truth_table("AB|");
		std::cout << "Formula: AB&\n";
		print_truth_table("AB&");
		std::cout << "Formula: AB^\n";
		print_truth_table("AB^");
		std::cout << "Formula: AB>\n";
		print_truth_table("AB>");
		std::cout << "Formula: AB=\n";
		print_truth_table("AB=");
		std::cout << "Formula: AA=\n";
		print_truth_table("AA=");
		std::cout << U_WHITE "Composition\n" NORMAL;
		std::cout << "Formula: ABC==\n";
		print_truth_table("ABC==");
		std::cout << "Formula: AB>C>\n";
		print_truth_table("AB>C>");
		std::cout << "Formula: AB>A>A>\n";
		print_truth_table("AB>A>A>");
	}
	{
		std::cout << "\t" B_WHITE "negation normal form" NORMAL ":\n";
		std::cout << U_WHITE "Basic tests\n" NORMAL;
		std::cout << "Formula `A` is `" << negation_normal_form("A") << "`\n";
		std::cout << "Formula `A!` is `" << negation_normal_form("A!") << "`\n";
		std::cout << "Formula `AB&!` is `" << negation_normal_form("AB&!") << "`\n";
		std::cout << "Formula `AB|!` is `" << negation_normal_form("AB|!") << "`\n";
		std::cout << "Formula `AB>!` is `" << negation_normal_form("AB>!") << "`\n";
		std::cout << "Formula `AB=!` is `" << negation_normal_form("AB=!") << "`\n";
		std::cout << U_WHITE "Composition\n" NORMAL;
		std::cout << "Formula `ABC||` is `" << negation_normal_form("ABC||") << "`\n";
		std::cout << "Formula `ABC||!` is `" << negation_normal_form("ABC||!") << "`\n";
		std::cout << "Formula `ABC|&` is `" << negation_normal_form("ABC|&") << "`\n";
		std::cout << "Formula `ABC&|` is `" << negation_normal_form("ABC&|") << "`\n";
		std::cout << "Formula `ABC&|!` is `" << negation_normal_form("ABC&|!") << "`\n";
		std::cout << "Formula `ABC^^` is `" << negation_normal_form("ABC^^") << "`\n";
		std::cout << "Formula `ABC>>` is `" << negation_normal_form("ABC>>") << "`\n";
	}
	{
		std::cout << "\t" B_WHITE "conjunctive normal form" NORMAL ":\n";
		std::cout << U_WHITE "Basic tests\n" NORMAL;
		std::cout << "Formula `A` is `" << conjunctive_normal_form("A") << "`\n";
		std::cout << "Formula `A!` is `" << conjunctive_normal_form("A!") << "`\n";
		std::cout << "Formula `AB&!` is `" << conjunctive_normal_form("AB&!") << "`\n";
		std::cout << "Formula `AB|!` is `" << conjunctive_normal_form("AB|!") << "`\n";
		std::cout << "Formula `AB>!` is `" << conjunctive_normal_form("AB>!") << "`\n";
		std::cout << "Formula `AB=!` is `" << conjunctive_normal_form("AB=!") << "`\n";
		std::cout << U_WHITE "Composition\n" NORMAL;
		std::cout << "Formula `ABC||` is `" << conjunctive_normal_form("ABC||") << "`\n";
		std::cout << "Formula `ABC||!` is `" << conjunctive_normal_form("ABC||!") << "`\n";
		std::cout << "Formula `ABC|&` is `" << conjunctive_normal_form("ABC|&") << "`\n";
		std::cout << "Formula `ABC&|` is `" << conjunctive_normal_form("ABC&|") << "`\n";
		std::cout << "Formula `ABC&|!` is `" << conjunctive_normal_form("ABC&|!") << "`\n";
		std::cout << "Formula `ABC^^` is `" << conjunctive_normal_form("ABC^^") << "`\n";
		std::cout << "Formula `ABC>>` is `" << conjunctive_normal_form("ABC>>") << "`\n";
	}
	{
		std::cout << "\t" B_WHITE "satisfiability" NORMAL ":\n";
		std::cout << std::boolalpha;
		std::cout << U_WHITE "Basic tests\n" NORMAL;
		std::cout << "Satisfiability of formula `A` is `" << sat("A") << "`\n";
		std::cout << "Satisfiability of formula `A!` is `" << sat("A!") << "`\n";
		std::cout << "Satisfiability of formula `AA|` is `" << sat("AA|") << "`\n";
		std::cout << "Satisfiability of formula `AA&` is `" << sat("AA&") << "`\n";
		std::cout << "Satisfiability of formula `AA!&` is `" << sat("AA!&") << "`\n";
		std::cout << "Satisfiability of formula `AA^` is `" << sat("AA^") << "`\n";
		std::cout << "Satisfiability of formula `AB^` is `" << sat("AB^") << "`\n";
		std::cout << "Satisfiability of formula `AB=` is `" << sat("AB=") << "`\n";
		std::cout << "Satisfiability of formula `AA>` is `" << sat("AA>") << "`\n";
		std::cout << "Satisfiability of formula `AA!>` is `" << sat("AA!>") << "`\n";
		std::cout << U_WHITE "Composition\n" NORMAL;
		std::cout << "Satisfiability of formula `ABC||` is `" << sat("ABC||") << "`\n";
		std::cout << "Satisfiability of formula `AB&A!B!&&` is `" << sat("AB&A!B!&&") << "`\n";
		std::cout << "Satisfiability of formula `ABCDE&&&&` is `" << sat("ABCDE&&&&") << "`\n";
		std::cout << "Satisfiability of formula `AAA^^` is `" << sat("AAA^^") << "`\n";
		std::cout << "Satisfiability of formula `ABCDE^^^^` is `" << sat("ABCDE^^^^") << "`\n";
		std::cout << std::noboolalpha;
	}
	{
		std::cout << "\t" B_WHITE "powerset" NORMAL ":\n";
		rsb::set<rsb::set<int32_t>> sets;
		rsb::set<int32_t> set;
		int32_t numbers[] = {0, 1, 2};
		

		for (int32_t test_index(0); test_index < 4; ++test_index)
		{
			set.clear();
			for (int32_t i(0); i < test_index; ++i)
				set.push_back(numbers[i]);
			sets = powerset(set);
			std::cout << '[';
			for (rsb::set<int32_t>::size_type i(0); i < set.size(); ++i)
			{
				std::cout << set[i];
				if (i < set.size() - 1)
					std::cout << ", ";
			}
			std::cout << "] gives [";
			for (rsb::set<rsb::set<int32_t>>::size_type i(0); i < sets.size(); ++i)
			{
				std::cout << '[';
				for (rsb::set<int32_t>::size_type j(0); j < sets[i].size(); ++j)
				{
					std::cout << sets[i][j];
					if (j < sets[i].size() - 1)
						std::cout << ", ";
				}
				std::cout << ']';
				if (i < sets.size() - 1)
					std::cout << ", ";
			}
			std::cout << "] (" << sets.size() << " subset)\n";
		}
	}
}