# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/07 15:13:54 by aait-mal          #+#    #+#              #
#    Updated: 2023/07/30 03:47:04 by obelaizi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = $(wildcard *.c Parsing/*.c Execution/*.c)
OBJ = $(SRC:.c=.o)
HEADER = minishell.h ./Libft/libft.h
CC = cc
FLAGS = -Wall -Wextra -Werror 

RL_INC = -I $(shell brew --prefix readline)/include
RL_LIB = -L $(shell brew --prefix readline)/lib

all : libft.a $(NAME)

libft.a : 
	make -C Libft all bonus

$(NAME) :  $(OBJ)
	$(CC) $(RL_LIB) $(OBJ) ./Libft/libft.a -o $(NAME) -lreadline 

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) $(RL_INC)  -c $< -o $@

clean :
	rm -rf $(OBJ)
	make -C Libft clean

fclean : clean
	rm -rf $(NAME)
	make -C Libft fclean

re : fclean all

.PHONY : all clean fclean re