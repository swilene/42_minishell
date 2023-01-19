/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:21:52 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/19 17:45:19 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

extern int	g_exit_code;

char	*search_variable(char *var_name, char *var, t_env *tmp)
{
	int		len;

	len = ft_strlen(var_name);
	while (tmp)
	{
		if (ft_strnstr(tmp->str, var_name, len) && tmp->str[len] == '=')
		{
			len++;
			var = ft_substr(tmp->str, &len, ft_strlen(tmp->str) - len);
			if (!var)
				return (printf("var: %s\n", strerror(ENOMEM)), NULL);
			return (var);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
