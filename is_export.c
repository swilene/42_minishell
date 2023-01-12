/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:23:18 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/12 17:15:40 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

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

void	big_arg(char *arg, char *quotes, t_env **env, t_env **var)
{
	char	*new;

	if (in_env(arg, env, quotes) == 0)
	{
		if (in_var(arg, env, var, quotes) == 0)
		{
			new = ft_strdup(arg);
			if (!new)
				return ;
			ft_envadd_back(env, ft_envnew(new, quotes));
		}
	}
}

void	little_arg(char *arg, t_env **env, t_env **var)
{
	t_env	*first_var;
	t_env	*tmp;
	int		len;
	char	*res;
	char	*quotes;

	first_var = (*var);
	len = ft_strlen(arg);
	tmp = NULL;
	while (*var)
	{
		if (ft_strncmp((*var)->str, arg, len) == 0 && (*var)->str[len] == '=')
		{
			res = ft_strdup((*var)->str);
			quotes = ft_strdup((*var)->quote);
			if (!res || !quotes)
				return ;
			ft_lstdelone(tmp, var, &first_var);
			ft_envadd_back(env, ft_envnew(res, quotes));
			free(quotes);
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
			big_arg(init->lexer->args[i], init->lexer->quotes[i], env, var);
		else
			little_arg(init->lexer->args[i], env, var);
		i++;
	}
	/*printf ("Print env :\n");
	print_list(env);
	printf ("Print var :\n");
	print_list(var);*/
}
