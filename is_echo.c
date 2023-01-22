/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:16:41 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/22 17:12:02 by saguesse         ###   ########.fr       */
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

int	write_arg(t_init *init, t_lexer *lexer, int j)
{
	if (!init->nb_pipe && lexer->fd_out)
	{
		if (write(lexer->fd_out, lexer->args[j], ft_strlen(lexer->args[j]))
			< 0)
			return (1);
	}
	else
		printf("%s", lexer->args[j]);
	if (lexer->args[j + 1])
	{
		if (!init->nb_pipe && lexer->fd_out)
		{
			if (write(lexer->fd_out, " ", 1) < 0)
				return (2);
		}
		else
			printf(" ");
	}
	return (0);
}

void	is_echo(t_lexer *lexer, t_init *init)
{
	int	j;
	int	n;

	n = 0;
	j = 1;
	if (lexer->args[j] && lexer->args[j][0] == '-')
		flags(lexer, &j, &n);
	while (lexer->args[j])
	{
		if (write_arg(init, lexer, j))
			return (perror("echo"));
		j++;
	}
	if (!n)
	{
		if (!init->nb_pipe && lexer->fd_out)
		{
			if (write(lexer->fd_out, "\n", 1) < 0)
				return (perror("echo"));
		}
		else
			printf("\n");
	}
}
