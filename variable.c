/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchantro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:13:36 by tchantro          #+#    #+#             */
/*   Updated: 2023/01/19 16:50:29 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

void	remplace_var_str(t_init *init, t_env *tmp)
{
	free(init->var->str);
	init->var->str = ft_strdup(tmp->str);
	free(tmp->str);
	free(tmp);
	tmp = NULL;
}

void	remplace_env_str(t_init *init, t_env *tmp)
{
	free(init->env->str);
	init->env->str = ft_strdup(tmp->str);
	free(tmp->str);
	free(tmp);
	tmp = NULL;
}

int	check_var(t_init *init, t_env *tmp)
{
	int		len;
	t_env	*first_var;

	first_var = init->var;
	len = var_len(tmp->str);
	if (first_var == NULL)
	{
		ft_envadd_back(&(init->var), tmp);
		return (1);
	}
	while (init->var)
	{
		if (ft_strncmp(init->var->str, tmp->str, len) == 0
			&& init->var->str[len] == '=')
		{
			remplace_var_str(init, tmp);
			init->var = first_var;
			return (1);
		}
		init->var = init->var->next;
	}
	init->var = first_var;
	return (0);
}

int	check_env(t_init *init, t_env *tmp)
{
	int		len;
	t_env	*first_env;

	first_env = init->env;
	len = var_len(tmp->str);
	while (init->env)
	{
		if (ft_strncmp(init->env->str, tmp->str, len) == 0
			&& init->env->str[len] == '=')
		{
			remplace_env_str(init, tmp);
			init->env = first_env;
			return (1);
		}
		init->env = init->env->next;
	}
	init->env = first_env;
	return (0);
}

int	check_envariables(char *word, t_init *init)
{
	int		i;
	t_env	*tmp;
	char	*var;

	i = 0;
	while (word[i])
	{
		if (word[i] == '=')
		{
			var = ft_strdup(word);
			if (!var)
				return (1);
			tmp = ft_envnew(var);
			if (!tmp)
				return (free(var), 2);
			if (check_env(init, tmp) == 0)
			{
				if (check_var(init, tmp) == 0)
					ft_envadd_back(&(init->var), tmp);
			}
			printf ("Print env :\n");
			print_list(&init->env);
			printf ("Print var :\n");
			print_list(&init->var);
			return (3);
		}
		i++;
	}
	return (0);
}
