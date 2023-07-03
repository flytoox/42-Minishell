# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obelaizi <obelaizi@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 19:41:28 by obelaizi          #+#    #+#              #
#    Updated: 2022/11/01 16:31:54 by obelaizi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS= -Wall -Wextra -Werror

SRCS= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c \
	ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
	ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c	ft_putnbr_fd.c

SRCS_BONUS= ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

OBJS= $(SRCS:.c=.o)

OBJS_BONUS= $(SRCS_BONUS:.c=.o)

all: $(NAME)

%.o: %.c libft.h
	cc -c $(FLAGS) $<

$(NAME): $(OBJS)
	@ar -r $(NAME) $(OBJS)

bonus: $(OBJS_BONUS)
	@ar -r $(NAME) $(OBJS_BONUS)

clean:
	@rm -f $(OBJS) $(OBJS_BONUS)

fclean:clean
	@rm -f $(NAME)

re: fclean all