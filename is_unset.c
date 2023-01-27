/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:23:44 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/27 17:18:59 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

extern int	g_exit_code;

int	var_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

int	unset_arg_len(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == '=')
			return (-1);
		i++;
	}
	return (i);
}

int	checkin_env(t_init *init, int len, int j)
{	
	t_env	*tmp;
	t_env	*first;

	first = init->env;
	tmp = NULL;
	while (init->env)
	{
		if (ft_strnstr(init->env->str, init->lexer->args[j], len)
			&& init->env->str[len] == '=')
		{
			ft_lstdelone(tmp, &(init->env), &first);
			if (init->env)
				init->env = first;
			return (1);
		}
		tmp = init->env;
		init->env = init->env->next;
	}
	init->env = first;
	return (0);
}

void	checkin_var(t_init *init, int len, int j)
{
	t_env	*tmp;
	t_env	*first_var;

	first_var = init->var;
	tmp = NULL;
	while (init->var)
	{
		if (ft_strnstr(init->var->str, init->lexer->args[j], len)
			&& init->var->str[len] == '=')
		{
			ft_lstdelone(tmp, &(init->var), &first_var);
			if (init->var)
				init->var = first_var;
			return ;
		}
		tmp = init->var;
		init->var = init->var->next;
	}
	init->var = first_var;
}

void	is_unset(t_init *init, t_env **env, t_env **var)
{
	int		len;
	int		j;

	(void)env;
	(void)var;
	j = 1;
	while (init->lexer->args[j])
	{
		len = unset_arg_len(init->lexer->args[j]);
		if (len > 0)
		{
			if (checkin_env(init, len, j) == 0)
			{
				checkin_var(init, len, j);
			}
		}
		j++;
	}
	g_exit_code = 0;
}
