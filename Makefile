# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/08 15:06:42 by ldutriez          #+#    #+#              #
#    Updated: 2023/03/15 16:39:03 by ldutriez         ###   ########.fr        #
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

BUILD_LOG = logs/Makefile.log

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
POWERSET_SRC = powerset.cpp powerset_tests.cpp
SET_EVALUATION_SRC = set_evaluation.cpp set_evaluation_tests.cpp
SFC_MAP_SRC = map.cpp map_tests.cpp

SRCS = main.cpp \
		$(ADDER_SRC) \
		$(MULTIPLIER_SRC) \
		$(GRAY_CODE_SRC) \
		$(TREE_PRINTER_SRC) \
		$(EVAL_FORMULA_SRC) \
		$(TRUTH_TABLE_SRC) \
		$(NEGATION_NORMAL_FORM_SRC) \
		$(CONJUNCTIVE_NORMAL_FORM_SRC) \
		$(SATISFIABILITY_SRC) \
		$(POWERSET_SRC) \
		$(SET_EVALUATION_SRC) \
		$(SFC_MAP_SRC)

OBJ_DIR = objs
OBJS = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

msg = $(shell echo "$(_PURPLE)A file named $(_YELLOW)$(BUILD_LOG)$(_PURPLE) contain the current build informations.$(_WHITE)")
useless := $(info $(msg))

# Make sure the logs directory exists.
useless := $(shell mkdir -p $(dir $(BUILD_LOG)))

# Split the log file between each run.
useless := $(shell echo "________________________________________________________________________________" >> $(BUILD_LOG); \
				echo "$(shell date) : \c" >> $(BUILD_LOG); \
				echo "building with : [$(MAKECMDGOALS)], DEBUG set to {$(DEBUG)}" >> $(BUILD_LOG))

all : $(NAME)

help:
	@printf "$(_PURPLE)Usage:\n"
	@printf "Type $(_BLUE)make run$(_PURPLE) to create and run the project binary.\n"
	@printf "Add $(_BLUE)DEBUG=fs$(_PURPLE) to compile with fsanitize and debug flags.\n"
	@printf "Add $(_BLUE)DEBUG=vl$(_PURPLE) to compile with valgrind and debug flags.\n"
	@printf "Add $(_BLUE)DEBUG=gdb$(_PURPLE) to compile with gdb and debug flags.$(_WHITE)\n"

$(OBJ_DIR) :
	@printf '-----\n'
	@printf 'Creating  $(_YELLOW)$(OBJ_DIR)$(_WHITE) ... '
	$(shell echo "$(shell date) : \c" >> $(BUILD_LOG) 2>&1; \
		echo "mkdir -p $(OBJ_DIR)" >> $(BUILD_LOG) 2>&1)
	$(eval ret_status := $(shell mkdir -p $(OBJ_DIR) >> $(BUILD_LOG) 2>&1; echo $$?))
	@if [ $(ret_status) -eq 0 ]; then \
		printf "$(_GREEN)Done$(_WHITE)\n"; \
	else \
		printf "$(_RED)Failed$(_WHITE)\n"; \
		exit $(ret_status); \
	fi

$(OBJ_DIR)/%.o : %.cpp | $(OBJ_DIR)
	@printf 'Compiling $(_YELLOW)%-43s$(_WHITE)' "$@ ... "
	$(shell echo "$(shell date) : \c" >> $(BUILD_LOG) 2>&1 ;\
		echo "$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@" >> $(BUILD_LOG) 2>&1)
	$(eval ret_status := $(shell $(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@ >> $(BUILD_LOG) 2>&1; echo $$?))
	@if [ $(ret_status) -eq 0 ]; then \
		printf "$(_GREEN)Done$(_WHITE)\r"; \
	else \
		printf "$(_RED)Failed$(_WHITE)\n"; \
		exit $(ret_status); \
	fi

$(NAME) : $(OBJS)
	@echo "\n-----\nCompiling $(_YELLOW)$(NAME)$(_WHITE) ... \c"
	$(shell echo "$(shell date) : \c" >> $(BUILD_LOG) 2>&1; \
		echo "$(CC) $(CFLAGS) $(OBJS) -o $(NAME)" >> $(BUILD_LOG) 2>&1)
	$(eval ret_status := $(shell $(CC) $(CFLAGS) $(OBJS) -o $(NAME) >> $(BUILD_LOG) 2>&1; echo $$?))
	@if [ $(ret_status) -eq 0 ]; then \
		echo "$(_GREEN)Done$(_WHITE)"; \
	else \
		echo "$(_RED)Failed$(_WHITE)"; \
		echo "$(_RED)Check the log file for more informations.$(_WHITE)"; \
		exit $(ret_status); \
	fi

run : ${NAME}
	@if [ "$(DEBUG)" = "fs" ]; then \
		echo "$(_PURPLE)Running with fsanitize flags.$(_WHITE)"; \
		./$(NAME) 2>&1; \
	elif [ "$(DEBUG)" = "vl" ]; then \
		echo "$(_PURPLE)Running with valgrind flags.$(_WHITE)"; \
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) 2>&1; \
	elif [ "$(DEBUG)" = "gdb" ]; then \
		echo "$(_PURPLE)Running with gdb flags.$(_WHITE)"; \
		gdb ./$(NAME); \
	else \
		echo "$(_PURPLE)Running without debug flags.$(_WHITE)"; \
		./$(NAME) 2>&1; \
	fi

clean_log:
	@echo "Cleaning $(_YELLOW)$(BUILD_LOG)$(_WHITE) ... \c"
	@cp /dev/null $(BUILD_LOG)
	@echo "$(_GREEN)Done$(_WHITE)";

clean :
	@echo "Deleting Objects Directory $(_YELLOW)$(OBJ_DIR)$(_WHITE) ... \c"
	@rm -rf $(OBJ_DIR)
	@echo "$(_GREEN)Done$(_WHITE)"

fclean : clean
	@echo "Deleting binary file $(_YELLOW)$(NAME)$(_WHITE) ... \c"
	@rm -f $(NAME)
	@echo "$(_GREEN)Done$(_WHITE)"

re : fclean all

.PHONY : all help run clean_log clean fclean re