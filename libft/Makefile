# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saguesse <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 09:58:29 by saguesse          #+#    #+#              #
#    Updated: 2023/01/17 17:40:11 by saguesse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra

PRINTF_PATH = ./ft_printf

PRINTF = $(PRINTF_PATH)/libftprintf.a

SRC = ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strdup.c \
	ft_calloc.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putnbr_fd.c \
	ft_putendl_fd.c \
	ft_strtrim.c \
	ft_itoa.c \
	ft_split.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_strcmp.c \
	get_next_line.c \
	ft_lstnew.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_dellist.c \
	remove_quotes.c \
	ft_lstsize.c \
	ft_lstdelone.c \
	ft_strcpy.c \
	str_isdigit.c \
	#ft_lstadd_front.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c \

HEADER = libft.h

HEADER_PRINTF = $(PRINTF_PATH)/libftprintf.h

OBJ = $(SRC:.c=.o)

$(NAME): $(PRINTF) $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(PRINTF):
	make -C $(PRINTF_PATH)

%.o : %.c $(HEADER) $(HEADER_PRINTF)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJ)
	make clean -C $(PRINTF_PATH)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(PRINTF_PATH)

re: fclean all

.PHONY: all clean fclean re
