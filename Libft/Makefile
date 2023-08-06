# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 19:41:28 by obelaizi          #+#    #+#              #
#    Updated: 2023/08/03 17:07:10 by aait-mal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS= -Wall -Wextra -Werror

SRCS= ft_isalnum.o ft_isascii.c ft_isdigit.o ft_strchr.c  ft_strlen.c\
ft_atoi.c    ft_isalpha.c ft_isascii.o ft_itoa.c    ft_strdup.c  ft_strncmp.c\
ft_isalnum.c ft_isalpha.o ft_isdigit.c ft_split.c   ft_strjoin.c ft_substr.c\


OBJS= $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c libft.h
	cc -c $(FLAGS) $<

$(NAME): $(OBJS)
	ar -r $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS) $(OBJS_BONUS)

fclean:clean
	@rm -f $(NAME)

re: fclean all