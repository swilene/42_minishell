/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:54:54 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/23 14:15:36 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

extern int	g_exit_code;

char	*only_dollar(char *str, t_list *tmp, int *i)
{
	(*i)++;
	if (!str)
		str = ft_strdup(tmp->word);
	else
		str = ft_strjoin_free(str, "$");
	if (!str)
		return (printf("$: %s\n", strerror(ENOMEM)), NULL);
	return (str);
}

char	*replace_var(char *str, char *var)
{
	if (var)
	{
		if (str)
			str = ft_strjoin_free(str, var);
		else
			str = ft_strdup(var);
		free(var);
		if (!str)
			return (printf("str: %s\n", strerror(ENOMEM)), NULL);
	}
	return (str);
}

static char	*parsing_word(t_list *tmp, t_init *init, int *i, char *str)
{
	char	*var;

	var = NULL;
	if (tmp->word[*i] == '$' && (tmp->word[*i + 1] == '\0'
			||tmp->word[*i + 1] == '"' || tmp->word[*i + 1] == '\''))
	{
		return (only_dollar(str, tmp, i));
	}
	else if (tmp->word[*i] == '$')
	{
		if (check_variable(i, tmp->word, init, &var))
			return (NULL);
	}
	else if (tmp->word[*i] == '"' || tmp->word[*i] == '\'')
	{
		if (quotes(tmp, i, &var, 0))
			return (NULL);
	}
	else
	{
		if (no_quotes(tmp, i, &var))
			return (NULL);
	}
	return (replace_var(str, var));
}

int	env_var(t_list *tmp, t_init *init, int i)
{
	char	*str;

	while (tmp)
	{
		i = 0;
		str = NULL;
		while (tmp->word[i])
		{
			str = parsing_word(tmp, init, &i, str);
			if (tmp->word[i] && tmp->word[i] != '$')
				i++;
		}
		if (str)
		{
			free(tmp->word);
			tmp->word = ft_strdup(str);
			free(str);
			if (!tmp->word)
				return (printf("ft_substr: %s\n", strerror(ENOMEM)), 2);
		}
		else
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
