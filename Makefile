# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/07 15:13:54 by aait-mal          #+#    #+#              #
#    Updated: 2023/08/03 17:04:22 by aait-mal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = ./Parsing/GarbageList.c ./Parsing/envLists.c ./Parsing/functionsHelpers1.c ./Parsing/parsing.c\
		./Parsing/cmdsLists.c ./Parsing/expand.c ./Parsing/functionsHelpers2.c ./Parsing/parsingHelper.c\
		./Parsing/customSplit.c ./Parsing/expandHelper.c ./Parsing/parsList.c\
		./Execution/builtins.c ./Execution/execute.c ./Execution/functionsHelpers2.c ./Execution/functionsHelpers4.c\
		./Execution/builtins1.c ./Execution/functionsHelpers1.c ./Execution/functionsHelpers3.c ./Execution/ft_perror.c	\
		minishell.c

OBJ = $(SRC:.c=.o)
HEADER = minishell.h ./Libft/libft.h
CC = cc
FLAGS = -Wall -Wextra -Werror

RL_INC = -I $(shell brew --prefix readline)/include
RL_LIB = -L $(shell brew --prefix readline)/lib

all : libft.a $(NAME)

libft.a :
	make -C Libft all

$(NAME) :  $(OBJ) ./Libft/libft.a
	$(CC) $(RL_LIB) $(OBJ) $(FLAGS) ./Libft/libft.a -o $(NAME) -lreadline

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