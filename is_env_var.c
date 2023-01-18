/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_env_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:09:33 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/18 17:56:26 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

extern int	g_exit_code;

char	*is_env_var(t_list *tmp, t_init *init)
{
	int		i;
	//int		j;
	int		len;
	char	*word;
	char	*str;
	char	*var;
	char	*var_name;


	//printf("%s\n", new->quotes[j]);
	while (tmp)
	{
		i = 0;
		str = NULL;
		while (tmp->word[i])
		{
			var = NULL;
			var_name = NULL;
			if (tmp->word[i] != '$')
			{
				len = i;
				while (tmp->word[i] && tmp->word[i] != '$')
					i++;
				printf("i = [%c]\n", tmp->word[i]);
				if (tmp->word[i] == '$')
					i++;
				if (tmp->word[i - 1] == '"' || tmp->word[i - 1] == '\'')
					i--;
				if (tmp->word[i + 1])
				{
					printf("1\n");
					word = ft_substr(tmp->word, &len, i - len);
				}
				else
					word = ft_substr(tmp->word, &len, i - len);
				printf("word [%s]\n", word);
				if (str)
					str = ft_strjoin(str, word);
				else
					str = ft_strdup(word);
				i++;
			}
			//else quotes
			if (tmp->word[i] == '\'')
			{
				i++;
				len = i;
				while (tmp->word[i] && tmp->word[i] != '\'')
					i++;
				word = ft_substr(tmp->word, &len, i - len);
				if (str)
					str = ft_strjoin(str, word);
				else
					str = ft_strdup(word);
			}
			else
			{
				if (tmp->word[i] == '"')
					i++;
				if (tmp->word[i] == '$')
					i++;
				len = i;
				while ((tmp->word[len] >= 'a' && tmp->word[len] <= 'z')
						|| (tmp->word[len] >= 'A' && tmp->word[len] <= 'Z')
						|| (tmp->word[len] >= '0' && tmp->word[len] <= '9')
						|| tmp->word[len] == '_' || tmp->word[len] == '?')
					len++;
				if (tmp->word[len] == '"')
					len--;
				printf("DEBUG len: %d\n", len);
				var_name = ft_substr(tmp->word, &i, len - i);
				//protection
				printf("DEBUG var_name: [%s]\n", var_name);
			}
			if (var_name)
			{
				if (var_name[0] == '?')
					var = ft_itoa(g_exit_code);
				else
				{
					var = search_variable(var_name, var, init->env);
					if (!var)
						var = search_variable(var_name, var, init->var);
				}
				printf("DEBUG var: %s\n", var);
				free(var_name);
				var_name = NULL;
			}
			if (var)
			{
				len = 0;
				if (str)
					str = ft_strjoin(str, var);
				else
					str = ft_strdup(var);
				free(var);
			}
			printf("DEBUG word[i]: [%c]\n", tmp->word[i]);
			/*if (tmp->word[i] == '"' || tmp->word[i] =='\'')
			{
				i++;
			}*/
		}
		printf("str: %s\n", str);
		if (str)
		{
			free(tmp->word);
			tmp->word = ft_strdup(str);
			free(str);
		}
		printf("DEBUG word: %s\n", tmp->word);
		tmp = tmp->next;
	}
	return ("ok");
}
