/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:16:41 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/11 11:56:08 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

extern int	g_exit_code;

static char	*quotes(int *i, char *str, t_init *init, t_lexer *lexer)
{
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\'')
		{
			write(lexer->fd_out, &str[*i], 1);
			(*i)++;
		}
	}
	else if (str[*i] == '"')
	{
		(*i)++;
		while (str[*i] && str[*i] != '"')
		{
			if (str[*i] == '$')
			{
				if (!write_variable(i, str, init, lexer))
					return (NULL);
			}
			if (str[*i] && str[*i] != '"')
				write(lexer->fd_out, &str[*i], 1);
			(*i)++;
		}
	}
	return ("ok");
}

static char	*variables(int *i, char *str, t_init *init, t_lexer *lexer)
{
	char	*nb;

	(*i)++;
	if (str[*i] == '\'')
	{
		(*i)--;
		if (!quotes(i, str, init, lexer))
			return (NULL);
	}
	if (str[*i] == '?')
	{
		nb = ft_itoa(g_exit_code);
		write(lexer->fd_out, nb, ft_strlen(nb));
		free(nb);
	}
	else if (str[*i] && str[*i] != '"' && str[*i] != '\'')
	{
		if (!write_variable(i, str, init, lexer))
			return (NULL);
	}
	else
		write(lexer->fd_out, "$", 1);
	(*i)++;
	return ("ok");
}

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

static char	*parsing_echo(t_init *init, t_lexer *lexer, int j, int *k)
{
	if (lexer->quotes[j][*k] == '\'' || lexer->quotes[j][*k] == '"')
	{
		if (!quotes(k, lexer->quotes[j], init, lexer))
			return (NULL);
	}
	else
	{
		if (lexer->quotes[j][*k] == '$')
		{
			if (!variables(k, lexer->quotes[j], init, lexer))
				return (NULL);
		}
		if (lexer->quotes[j][*k])
			write(lexer->fd_out, &lexer->quotes[j][*k], 1);
	}
	if (lexer->quotes[j][*k])
		(*k)++;
	return ("ok");
}

void	is_echo(t_init *init, t_lexer *lexer, int i)
{
	int	j;
	int	n;
	int	k;

	n = 0;
	j = 1;
	if (init->nb_pipe && i != init->nb_pipe && !lexer->fd_out)
		lexer->fd_out = init->fd_pipe[i][1];
	else if (!lexer->fd_out)
		lexer->fd_out = STDOUT_FILENO;
	if (lexer->args[j] && lexer->args[j][0] == '-')
		flags(lexer, &j, &n);
	while (lexer->quotes[j])
	{
		k = 0;
		while (lexer->quotes[j][k])
		{
			if (!parsing_echo(init, lexer, j, &k))
				return ;
		}
		if (lexer->quotes[j + 1])
			write(lexer->fd_out, " ", 1);
		j++;
	}
	if (!n)
		write(lexer->fd_out, "\n", 1);
}
