# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/08 15:06:42 by ldutriez          #+#    #+#              #
#    Updated: 2023/03/06 15:48:45 by ldutriez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_GREY=	$'\033[30m
_RED=	$'\033[31m
_GREEN=	$'\033[32m
_YELLOW=$'\033[33m
_BLUE=	$'\033[34m
_PURPLE=$'\033[35m
_CYAN=	$'\033[36m
_WHITE=	$'\033[37m

NAME = RSB
CC = c++
CFLAGS = -Wall -Wextra -Werror

DEBUG =
ifeq ($(DEBUG), fs)
	CFLAGS += -fsanitize=address
	CFLAGS += -g3
	CFLAGS += -O0
	msg = $(shell echo "$(_PURPLE)fsanitize and debug flags are added.$(_WHITE)")
	useless := $(info $(msg))
else ifeq ($(DEBUG), vl)
	CFLAGS += -g3
	CFLAGS += -O0
	msg = $(shell echo "$(_PURPLE)Valgrind and debug flags are added. Take care to rebuild the program entirely if you already used valgrind.$(_WHITE)")
	useless := $(info $(msg))
else
	CFLAGS += -O3
	msg = $(shell echo "$(_PURPLE)Debug mode not enabled. Optimization flags are added.$(_WHITE)")
	useless := $(info $(msg))
endif

SRC_DIR = $(shell find srcs -type d)

INC_DIR = $(shell find includes -type d)
IFLAGS = $(foreach dir, $(INC_DIR), -I$(dir))

vpath %.cpp $(foreach dir, $(SRC_DIR), $(dir):)

ADDER_SRC = adder.cpp adder_tests.cpp
MULTIPLIER_SRC = multiplier.cpp multiplier_tests.cpp
GRAY_CODE_SRC = gray_code.cpp gray_code_tests.cpp
TREE_PRINTER_SRC = ast_printer.cpp
EVAL_FORMULA_SRC = eval_formula.cpp eval_formula_tests.cpp
TRUTH_TABLE_SRC = truth_table.cpp truth_table_tests.cpp
NEGATION_NORMAL_FORM_SRC = negation_normal_form.cpp negation_normal_form_tests.cpp
CONJUNCTIVE_NORMAL_FORM_SRC = conjunctive_normal_form.cpp conjunctive_normal_form_tests.cpp
SATISFIABILITY_SRC = sat.cpp sat_tests.cpp

SRCS = main.cpp \
		$(ADDER_SRC) \
		$(MULTIPLIER_SRC) \
		$(GRAY_CODE_SRC) \
		$(TREE_PRINTER_SRC) \
		$(EVAL_FORMULA_SRC) \
		$(TRUTH_TABLE_SRC) \
		$(NEGATION_NORMAL_FORM_SRC) \
		$(CONJUNCTIVE_NORMAL_FORM_SRC) \
		$(SATISFIABILITY_SRC)

OBJ_DIR = objs
OBJS = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

all : $(NAME)

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.cpp | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	@rm -rf $(OBJ_DIR)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re