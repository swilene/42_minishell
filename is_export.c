/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:23:18 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/27 17:18:21 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

extern int	g_exit_code;

int	verif_export_args(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	big_arg(char *arg, t_env **env, t_env **var)
{
	char	*new;

	if (in_env(arg, env) == 0)
	{
		if (in_var(arg, env, var) == 0)
		{
			new = ft_strdup(arg);
			if (!new)
				return ;
			ft_envadd_back(env, ft_envnew(new));
		}
	}
}

void	little_arg(char *arg, t_env **env, t_env **var)
{
	t_env	*first_var;
	t_env	*tmp;
	int		len;
	char	*res;

	first_var = (*var);
	len = ft_strlen(arg);
	tmp = NULL;
	while (*var)
	{
		if (ft_strncmp((*var)->str, arg, len) == 0 && (*var)->str[len] == '=')
		{
			res = ft_strdup((*var)->str);
			if (!res)
				return ;
			ft_lstdelone(tmp, var, &first_var);
			ft_envadd_back(env, ft_envnew(res));
			if (*var)
				(*var) = first_var;
			return ;
		}
		tmp = (*var);
		(*var) = (*var)->next;
	}
	(*var) = first_var;
}

void	is_export(t_init *init, t_env **env, t_env **var)
{
	int		i;

	i = 1;
	while (init->lexer->args[i])
	{
		if (verif_export_args(init->lexer->args[i]) == 1)
			big_arg(init->lexer->args[i], env, var);
		else
			little_arg(init->lexer->args[i], env, var);
		i++;
	}
	g_exit_code = 0;
}
