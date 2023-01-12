/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_env_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:09:33 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/12 16:26:34 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

extern int	g_exit_code;

char	*is_env_var(t_init *init, char *word, t_lexer *new);

int	search_env_var(t_env *tmp, char *word, t_lexer *new, t_init *init)
{
	char	*env_var;
	char	**var;
	char	*str;
	int		nb;
	int		i;

	var = NULL;
	nb = 1;
	env_var = ft_strtrim(word, "$");
	if (!env_var)
		return (-1);
	while (tmp)
	{
		i = 0;
		while (tmp->str[i] && tmp->str[i] != '=')
			i++;
		nb = ft_strncmp(tmp->str, env_var, ft_strlen(env_var));
		if (!nb)
			break ;
		tmp = tmp->next;
	}
	free(env_var);
	if (!nb)
	{
		i++;
		str = ft_substr(tmp->str, &i, ft_strlen(tmp->str) - i);
		if (!str)
			return (-2);
		var = ft_split(str, ' ');
		free(str);
		if (!var)
			return (-3);
		if (var[0][0] == '$')
			is_env_var(init, var[0], new);
		else if (!check_builtin(var[0]))
		{
			new->cmd = ft_strdup(var[0]);
			if (!new->cmd)
				return (free_str(var), -4);
		}
		else
		{
			new->env_var = tmp;
			new->builtin = ft_strdup(var[0]);
		}
		if (!new->args)
			new->args = var;
		else
			free_str(var);
		return (nb);
	}
	return (1);
}

char	*is_env_var(t_init *init, char *word, t_lexer *new)
{
	int		i;
	int		len;
	int		err;
	char	*var;

	i = 1;
	//printf("%s\n", new->quotes[0]);
	if (new->quotes[0][0] == '\'')
	{
		new->cmd = ft_strdup(word);
		if (!new->cmd)
			return (NULL);
	}
	else
	{
		while (word[i])
		{
			len = i - 1;
			while (word[i] && word[i] != '$')
				i++;
			var = ft_substr(word, &len, i);
			if (!var)
				return (NULL);
			if (var[len - i + 1] == '?')
			{
				new->cmd = ft_itoa(g_exit_code);
				if (!new->cmd)
					return (NULL);
			}
			else
			{
				err = search_env_var(init->env, var, new, init);
				if (err > 0)
				{
					err = search_env_var(init->var, var, new, init);
					if (err < 0)
						return (free(var), NULL);
				}
				else if (err < 0)
					return (free(var), NULL);
			}
			free(var);
			if (word[i])
				i++;
		}
	}
	return ("ok");
}
