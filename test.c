/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:54:54 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/18 18:20:53 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

extern int	g_exit_code;

char	*check_variable(int *i, char *str)
{
	char	*var_name;
	char	*var;
	int		j;

	j = *i;
	if (str[*i] == '?')
	{
		var = ft_itoa(g_exit_code);
		if (!var)
			return (NULL);
	}
	else
	{
		while (str[j] && (ft_isalnum(str[j]) == 1 || str[j] == '_'))
			j++;
		var_name = ft_substr(str, i, j - (*i));
		if (!var_name)
			return (printf("var_name: %s\n", strerror(ENOMEM)), NULL);
		(*i)--;
		var = search_variable(var_name, var, init->env);
		if (!var)
			var = search_variable(var_name, var, init->var);
	}
	free(var_name);
	(*i)++;
	return (var);
}

char	*is_env_var(t_list *tmp, t_init *init)
{
	int		i;
	int		len;
	char	*word;
	char	*str;
	char	*var;
	char	*var_name;

	while (tmp)
	{
		i = 0;
		str = NULL;
		while (tmp->word[i])
		{
			var = NULL;
			var_name = NULL;
			if (tmp->word[i] == '$')
				var = check_variable(&i, tmp->word);
			else if (tmp->word[i] == '"')
			{

			}
			else if (tmp->word[i] == '\'')
			{
				i++;
				j = i;
				while (str[i] && str[i] != '\'')
					i++;
				var = ft_substr(str, &j, i - j);
			}
			else
}
