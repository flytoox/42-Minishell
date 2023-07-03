# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/07 15:13:54 by aait-mal          #+#    #+#              #
#    Updated: 2023/06/08 21:43:38 by obelaizi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC =	$(wildcard *.c)
OBJ = $(SRC:.c=.o)
HEADER = minishell.h
CC = cc
FLAGS = -Wall -Wextra -Werror

all : libft.a $(NAME)

libft.a : 
	@make -C Libft all bonus

$(NAME) :  $(OBJ)
	$(CC) ./Libft/libft.a $(OBJ) -o $(NAME) -lreadline

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ)
	make -C Libft clean

fclean : clean
	rm -rf $(NAME)
	make -C Libft fclean

re : fclean all

.PHONY : all clean fclean re
