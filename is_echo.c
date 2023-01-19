/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:16:41 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/19 17:45:04 by saguesse         ###   ########.fr       */
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

void	is_echo(t_init *init, t_lexer *lexer, int i)
{
	int	j;
	int	n;

	n = 0;
	j = 1;
	if (init->nb_pipe && i != init->nb_pipe && !lexer->fd_out)
		lexer->fd_out = init->fd_pipe[i][1];
	else if (!lexer->fd_out)
		lexer->fd_out = STDOUT_FILENO;
	if (lexer->args[j] && lexer->args[j][0] == '-')
		flags(lexer, &j, &n);
	while (lexer->args[j])
	{
		if (write(lexer->fd_out, lexer->args[j], ft_strlen(lexer->args[j])) < 0)
			perror("echo");
		j++;
	}
	if (!n)
	{
		if (write(lexer->fd_out, "\n", 1) < 0)
			return (perror("echo"));
	}
}
