/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_env_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:54:54 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/22 19:31:23 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

extern int	g_exit_code;

char *test(t_list *tmp, t_init *init)
{
	int		i;
	int		j;
	char	*str;
	char	*var;

	i = 0;
	str = NULL;
	while (tmp->word[i])
	{
		var = NULL;
		if (tmp->word[i] == '$' && tmp->word[i + 1] == '\0')
		{
			if (!str)
				str = ft_strdup(tmp->word);
			else
				str = ft_strjoin_free(str, "$");
			return (str);
		}
		else if (tmp->word[i] == '$')
		{
			if (check_variable(&i, tmp->word, init, &var))
				return (NULL);
		}
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
				str = ft_strjoin_free(str, var);
			else
				str = ft_strdup(var);
			free(var);
		}
		printf("%c\n", tmp->word[i]);
		if (tmp->word[i] && tmp->word[i] != '$')
			i++;
	}
	return (str);
}


int	is_env_var(t_list *tmp, t_init *init)
{
	char	*str;

	while (tmp)
	{
		str = test(tmp, init);
		if (str)
		{
			free(tmp->word);
			tmp->word = ft_strdup(str);
			free(str);
		}
		else
		{
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
