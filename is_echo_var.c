/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_echo_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:35:02 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/05 10:04:58 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

extern int	g_exit_code;

static void	quotes(int *i, char *str, t_init *init, t_lexer *lexer);

static void	search_variable(char *var_name, t_env *tmp, t_lexer *lexer)
{
	char	*var;
	int		len;

	len = ft_strlen(var_name);
	while (tmp)
	{
		if (ft_strnstr(tmp->str, var_name, len) && tmp->str[len] == '=')
		{
			len++;
			var = ft_substr(tmp->str, &len, ft_strlen(tmp->str) - len);
			if (var)
			{
				write(lexer->fd_out, var, ft_strlen(var));
				free(var);
			}
			break ;
		}
		tmp = tmp->next;
	}
}

static void	write_variable(int *i, char *str, t_init *init, t_lexer *lexer)
{
	char	*var_name;
	int		j;

	(void)init;
	j = *i;
	while (str[j] && ((str[j] >= 'a' && str[j] <= 'z') || (str[j] >= 'A'
				&& str[j] <= 'Z') || str[j] == '_'))
		j++;
	var_name = ft_substr(str, i, j - (*i));
	(*i)--;
	search_variable(var_name, init->env, lexer);
	search_variable(var_name, init->var, lexer);
}

static void	variables(int *i, char *str, t_init *init, t_lexer *lexer)
{
	char	*nb;

	(*i)++;
	/*if (str[*i] == '\'')
	{
		(*i)--;
		quotes(i, str, init, lexer);
	}*/
	if (str[*i] == '?')
	{
		nb = ft_itoa(g_exit_code);
		write(lexer->fd_out, nb, ft_strlen(nb));
	}
	else if (str[*i] && str[*i] != '"' && str[*i] != '\'')
		write_variable(i, str, init, lexer);
	else
		write(lexer->fd_out, "$", 1);
	(*i)++;
}

static void	quotes(int *i, char *str, t_init *init, t_lexer *lexer)
{
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
			variables(i, str, init, lexer);
		if (str[*i] && str[*i] != '"')
			write(lexer->fd_out, &str[*i], 1);
		(*i)++;
	}
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

void	is_echo_var(t_init *init, t_lexer *lexer, int i)
{
	int	j;
	int	n;
	int	q;
	int	k;

	n = 0;
	if (init->nb_pipe && i != init->nb_pipe && !lexer->fd_out)
		lexer->fd_out = init->fd_pipe[i][1];
	else if (!lexer->fd_out)
		lexer->fd_out = STDOUT_FILENO;
	j = 1;
	if (lexer->args[j] && lexer->args[j][0] == '-')
		flags(lexer, &j, &n);
	k = 0;
	while (lexer->env_var->quote[k] != '=')
		k++;
	if (lexer->env_var->quote[k + 1] == '"')
		q = 1;
	else
		q = 0;
	while (lexer->args[j])
	{
		k = 0;
		if (q)
			quotes(&k, lexer->args[j], init, lexer);
		else
		{
			while (lexer->args[j][k])
			{
				write(lexer->fd_out, &lexer->args[j][k], 1);
				k++;
			}
		}
		if (lexer->args[j][k])
			k++;
		if (lexer->args[j + 1])
			write(lexer->fd_out, " ", 1);
		j++;
	}
	if (!n)
		write(lexer->fd_out, "\n", 1);
}
