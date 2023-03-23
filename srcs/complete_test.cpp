/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_test.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 01:35:51 by ldutriez          #+#    #+#             */
/*   Updated: 2023/03/23 02:16:51 by ldutriez         ###   ########.fr       */
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
}