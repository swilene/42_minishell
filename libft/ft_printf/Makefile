# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saguesse <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 09:58:29 by saguesse          #+#    #+#              #
#    Updated: 2022/09/07 12:47:21 by saguesse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRC = ft_printf.c \
	ft_putchar.c \
	ft_putstr.c \
	ft_putnbr.c \
	ft_putnbr_unsigned.c \
	ft_putnbr_hexa.c \
	ft_putptr.c \
	ft_strlen.c \
	ft_strchr.c \

HEADER = libftprintf.h

OBJ = $(SRC:.c=.o)

$(NAME): $(LIBFT) $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME) 

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
