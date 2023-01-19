/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_env_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:54:54 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/19 17:51:34 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

extern int	g_exit_code;

char	*check_variable(int *i, char *str, t_init *init)
{
	char	*var_name;
	char	*var;
	int		j;

	(*i)++;
	j = *i;
	var = NULL;
	var_name =  NULL;
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
	if (var_name)
		free(var_name);
	(*i)++;
	return (var);
}

char	*is_env_var(t_list *tmp, t_init *init)
{
	int		i;
	int		j;
	char	*str;
	char	*var;

	while (tmp)
	{
		i = 0;
		str = NULL;
		while (tmp->word[i])
		{
			var = NULL;
			if (tmp->word[i] == '$')
				var = check_variable(&i, tmp->word, init);
			else if (tmp->word[i] == '"')
			{
				i++;
				j = i;
				while (tmp->word[i] && tmp->word[i] != '"' && tmp->word[i] != '$')
					i++;
				i--;
				if (i - j >= 0)
					var = ft_substr(tmp->word, &j, i - j + 1);
			}
			else if (tmp->word[i] == '\'')
			{
				i++;
				j = i;
				while (tmp->word[i] && tmp->word[i] != '\'')
					i++;
				var = ft_substr(tmp->word, &j, i - j);
			}
			else
			{
				j = i;
				while (tmp->word[i] && tmp->word[i] != '"'
						&& tmp->word[i] != '\'' && tmp->word[i] != '$')
					i++;
				i--;
				if (i - j >= 0)
					var = ft_substr(tmp->word, &j, i - j + 1);
			}
			if (var)
			{
				if (str)
					str = ft_strjoin(str, var);
				else
					str = ft_strdup(var);
				free(var);
			}
			if (tmp->word[i] && tmp->word[i] != '$')
				i++;
		}
		if (str)
		{
			free(tmp->word);
			tmp->word = ft_strdup(str);
			free(str);
		}
		tmp = tmp->next;
	}
	return ("ok");
}
