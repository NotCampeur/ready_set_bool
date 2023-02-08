# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/08 15:06:42 by ldutriez          #+#    #+#              #
#    Updated: 2023/02/08 15:32:53 by ldutriez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RSB
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

SRC_DIR = adder

vpath %.cpp $(foreach dir, $(SRC_DIR), $(dir):)

ADDER_SRC = adder.cpp

SRCS = main.cpp \
		$(ADDER_SRC)

OBJ_DIR = objs
OBJS = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

all : $(NAME)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re