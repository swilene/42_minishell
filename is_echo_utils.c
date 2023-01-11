/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:21:52 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/11 10:53:30 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

char	*search_variable(char *var_name, t_env *tmp, t_lexer *lexer)
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
			if (!var)
				return (printf("var: %s\n", strerror(ENOMEM)), NULL);
			write(lexer->fd_out, var, ft_strlen(var));
			free(var);
			break ;
		}
		tmp = tmp->next;
	}
	return ("ok");
}

char	*write_variable(int *i, char *str, t_init *init, t_lexer *lexer)
{
	char	*var_name;
	int		j;

	(void)init;
	j = *i;
	while (str[j] && ((str[j] >= 'a' && str[j] <= 'z') || (str[j] >= 'A'
				&& str[j] <= 'Z') || str[j] == '_'))
		j++;
	var_name = ft_substr(str, i, j - (*i));
	if (!var_name)
		return (printf("var_name: %s\n", strerror(ENOMEM)), NULL);
	(*i)--;
	if (!search_variable(var_name, init->env, lexer))
		return (free(var_name), NULL);
	if (!search_variable(var_name, init->var, lexer))
		return (free(var_name), NULL);
	free(var_name);
	(*i)++;
	return ("ok");
}
