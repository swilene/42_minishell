/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:16:41 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/20 10:52:01 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

extern int	g_exit_code;

static void	flags(t_lexer *lexer, int *j, int *n)
{
	int	i;

	while (lexer->args[*j])
	{
		if (lexer->args[*j][0] != '-')
			return ;
		i = 1;
		if (!lexer->args[*j][i])
			return ;
		while (lexer->args[*j][i] == 'n')
			i++;
		if (lexer->args[*j][i])
			return ;
		(*j)++;
		(*n)++;
	}
}

void	is_echo(t_lexer *lexer)
{
	int	j;
	int	n;

	n = 0;
	j = 1;
	if (lexer->args[j] && lexer->args[j][0] == '-')
		flags(lexer, &j, &n);
	while (lexer->args[j])
	{
		if (write(lexer->fd_out, lexer->args[j], ft_strlen(lexer->args[j])) < 0)
			perror("echo");
		if (lexer->args[j + 1])
		{
			if (write(lexer->fd_out, " ", 1) < 0)
				perror("echo");
		}
		j++;
	}
	if (!n)
	{
		if (write(lexer->fd_out, "\n", 1) < 0)
			return (perror("echo"));
	}
}
