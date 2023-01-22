/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:49:40 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/22 19:15:15 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

extern int	g_exit_code;

int	not_exit_code(int *i, char *str, t_init *init, char **var) 
{
	int		err;
	int		j;
	char	*var_name;

	j = *i;
	while (str[j] && (ft_isalnum(str[j]) == 1 || str[j] == '_'))
		j++;
	var_name = ft_substr(str, i, j - (*i));
	printf("var_name: %s\n", var_name);
	if (!var_name)
		return (printf("ft_substr: %s\n", strerror(ENOMEM)), 2);
	(*i)--;
	err = search_variable(var_name, var, init->env);
	if (err == 2)
	{
		err = search_variable(var_name, var, init->var);
		if (err == 1)
			return (free(var_name), 3);
	}
	else if (err == 1)
		return (free(var_name), 4);
	if (var_name)
		free(var_name);
	return (0);
}

int	check_variable(int *i, char *str, t_init *init, char **var)
{

	if (str[*i + 1] != '\0')
		(*i)++;
	*var = NULL;
	if (str[*i] == '?')
	{
		*var = ft_itoa(g_exit_code);
		if (!(*var))
			return (1);
	}
	else
	{
		if (not_exit_code(i, str, init, var))
			return (2);
	}
	(*i)++;
	return (0);
}

