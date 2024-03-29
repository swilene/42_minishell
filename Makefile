# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saguesse <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/07 14:54:21 by saguesse          #+#    #+#              #
#    Updated: 2023/01/23 13:06:05 by saguesse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc -g3

CFLAGS = -Wall -Werror -Wextra

LIBFT_PATH = ./libft

LIBFT = $(LIBFT_PATH)/libft.a

PRINTF_PATH = ./libft/ft_printf

PRINTF = $(PRINTF_PATH)/libftprintf.a

SRC = main.c \
	first_parsing.c \
	cut_sentence.c \
	lexer.c \
	lexer_utils.c \
	redirection.c \
	clear.c \
	pipes.c \
	path.c \
	signal.c \
	do_dup.c \
	do_dup_utils.c \
	parent_process.c \
	execution.c \
	is_cmd.c \
	heredoc.c \
	is_pwd.c \
	is_env.c \
	is_cd.c \
	is_export.c \
	is_unset.c \
	is_exit.c \
	is_echo.c \
	variable.c \
	init_files.c \
	close_fds.c \
	is_export_bis.c \
	env_var.c \
	split_word.c \
	search_variable.c \
	check_variable.c \
	quotes.c \
	
HEADER = structures.h \
	prototypes.h \

HEADER_LIBFT = $(LIBFT_PATH)/libft.h

HEADER_PRINTF = $(PRINTF_PATH)/libftprintf.h

OBJ = $(SRC:.c=.o)

$(NAME): $(PRINTF) $(LIBFT) $(OBJ)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJ) $(LIBFT) $(PRINTF) -L/usr/lib -lreadline

$(LIBFT):
	make -C $(LIBFT_PATH)

$(PRINTF):
	make -C $(PRINTF_PATH)

%.o : %.c $(HEADER) $(HEADER_LIBFT) $(HEADER_PRINTF)
	$(CC) $(CFLAGS) -c $< -o $@ -I . -I libft -I libft/ft_printf -I/usr/include

all: $(NAME) 

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_PATH)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_PATH)

re: fclean
	make all

.PHONY: all clean fclean re
