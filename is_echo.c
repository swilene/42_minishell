/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:16:41 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/11 17:20:24 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

extern int	g_exit_code;

static char	*quotes(int *i, char *str, t_lexer *lexer, t_init *init)
{
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\'')
		{
			if (write(lexer->fd_out, &str[*i], 1) < 0)
				return (perror("echo"), NULL);
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
				(*i)++;
				if (!write_variable(i, str, lexer, init))
					return (NULL);
			}
			if (str[*i] && str[*i] != '"')
			{
				if (write(lexer->fd_out, &str[*i], 1) < 0)
					return (perror("echo"), NULL);
			}
			(*i)++;
		}
	}
	return ("ok");
}

static char	*variables(int *i, char *str, t_lexer *lexer, t_init *init)
{
	char	*nb;

	(*i)++;
	if (str[*i] == '\'')
	{
		(*i)--;
		if (!quotes(i, str, lexer, init))
			return (NULL);
	}
	if (str[*i] == '?')
	{
		nb = ft_itoa(g_exit_code);
		if (write(lexer->fd_out, nb, ft_strlen(nb)) < 0)
		{
			free(nb);
			return (perror("echo"), NULL);
		}
		free(nb);
		(*i)++;
	}
	else if (str[*i] && str[*i] != '"' && str[*i] != '\'')
	{
		if (!write_variable(i, str, lexer, init))
			return (NULL);
	}
	else
	{
		if (write(lexer->fd_out, "$", 1) < 0)
			return (perror("echo"), NULL);
	}
	if (str[*i])
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

static char	*parsing_echo(t_lexer *lexer, int j, int *k, t_init *init)
{
	if (lexer->quotes[j][*k] == '\'' || lexer->quotes[j][*k] == '"')
	{
		if (!quotes(k, lexer->quotes[j], lexer, init))
			return (NULL);
	}
	else
	{
		if (lexer->quotes[j][*k] == '$')
		{
			if (!variables(k, lexer->quotes[j], lexer, init))
				return (NULL);
		}
		if (lexer->quotes[j][*k])
		{
			if (write(lexer->fd_out, &lexer->quotes[j][*k], 1) < 0)
				return (perror("echo"), NULL);
		}
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
			if (!parsing_echo(lexer, j, &k, init))
				return ;
		}
		if (lexer->quotes[j + 1])
		{
			if (write(lexer->fd_out, " ", 1) < 0)
				return (perror("echo"));
		}
		j++;
	}
	if (!n)
	{
		if (write(lexer->fd_out, "\n", 1) < 0)
			return (perror("echo"));
	}
}
