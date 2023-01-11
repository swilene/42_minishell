/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:49:14 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/11 18:03:21 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

extern int	g_exit_code;

int	first_errors(char *line, int *i)
{
	int		j;
	char	*word;

	if (!((line[*i] >= 'a' && line[*i] <= 'z') || line[*i] == '$' || line[*i]
			== '>' || line[*i] == '<' || line[*i] == '"' || line[*i] == '\''
			|| (line[*i] >= 'A' && line[*i] <= 'Z') || line[*i] == '.'
			|| line[*i] == '/'))
	{
		if (line[*i] == '|' || line[*i] == '(' || line[*i] == ')'
			|| line[*i] == '&')
		{
			g_exit_code = 2;
			return (printf("syntax error\n"), 1);
		}
		else
		{
			j = *i;
			while (line[j] != ' ' && line[j] != '\t' && line[j])
				j++;
			word = ft_substr(line, i, j - *i);
			g_exit_code = 127;
			printf("%s: command not found\n", word);
			return (free(word), 2);
		}
	}
	return (0);
}

void	check_quotes(char *line, int i, int *quotes)
{
	while (line[i])
	{
		if (line[i] == '"')
		{
			*quotes = 2;
			while (line[i] && *quotes != 0)
			{
				i++;
				if (line[i] && line[i] == '"')
					*quotes = 0;
			}
		}
		else if (line[i] == '\'')
		{
			*quotes = 1;
			while (line[i] && *quotes != 0)
			{
				i++;
				if (line[i] && line[i] == '\'')
					*quotes = 0;
			}
		}
		if (line[i])
			i++;
	}
}

int	parsing_line(char *line, t_init *init)
{
	int	i;
	int	quotes;

	i = 0;
	while (line[i] == ' ' && line[i])
		i++;
	if (!line[i] || line[i] == '#' || line[i] == ':')
		return (g_exit_code = 0, 1);
	if (line[i] == '!')
		return (g_exit_code = 1, 2);
	if (first_errors(line, &i))
		return (3);
	quotes = 0;
	check_quotes(line, 0, &quotes);
	if (quotes)
		return (printf("not managed by the subject\n"), 3);
	cut_sentence(init, line, &i, 0);
	return (0);
}
