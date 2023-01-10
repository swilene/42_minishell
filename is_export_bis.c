/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_export_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchantro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:48:48 by tchantro          #+#    #+#             */
/*   Updated: 2023/01/04 14:31:03 by tchantro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

int	big_arg_len(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '=')
		i++;
	return (i);
}

int	in_env(char *arg, t_env **env)
{
	t_env	*first;
	int		len;
	char	*new;

	first = (*env);
	len = big_arg_len(arg);
	while (*env)
	{
		if (ft_strncmp((*env)->str, arg, len) == 0 && (*env)->str[len] == '=')
		{
			new = ft_strdup(arg);
			if (!new)
				return (2);
			free((*env)->str);
			(*env)->str = new;
			(*env) = first;
			return (1);
		}
		(*env) = (*env)->next;
	}
	(*env) = first;
	return (0);
}

int	in_var(char *arg, t_env **env, t_env **var)
{
	t_env	*first_var;
	t_env	*tmp;
	char	*new;

	first_var = (*var);
	tmp = NULL;
	while (*var)
	{
		if (ft_strncmp((*var)->str, arg, big_arg_len(arg)) == 0
			&& (*var)->str[big_arg_len(arg)] == '=')
		{
			new = ft_strdup(arg);
			if (!new)
				return (2);
			ft_lstdelone(tmp, var, &first_var);
			ft_envadd_back(env, ft_envnew(new));
			if (*var)
				(*var) = first_var;
			return (1);
		}
		tmp = (*var);
		(*var) = (*var)->next;
	}
	(*var) = first_var;
	return (0);
}
