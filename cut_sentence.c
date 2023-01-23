/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_sentence.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:05:01 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/23 14:58:26 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

int	is_quote(char *line, int *j, int quotes)
{
	if (line[*j] == '\'')
	{
		(*j)++;
		while (line[*j] && (quotes % 2 || ft_isspace(line[(*j)]) == 0))
		{
			if (line[*j] == '\'')
				quotes++;
			(*j)++;
		}
	}
	else if (line[*j] == '"')
	{
		(*j)++;
		while (line[*j] && (quotes % 2 || ft_isspace(line[(*j)]) == 0))
		{
			if (line[*j] == '"')
				quotes++;
			(*j)++;
		}
	}
	else
		return (1);
	return (0);
}

int	is_word(char *line, int *j)
{
	if (ft_isalnum(line[*j]) == 1 || ft_isspace(line[*j]) == 1
		|| line[*j] == '#' || line[*j] == '-' || line[*j] == '.'
		|| line[*j] == '~' || line[*j] == '/' || line[*j] == '='
		|| line[*j] == '[')
	{
		while (line[*j] && (!(ft_isspace(line[*j]) == 1 || line[*j] == '|')))
		{
			if (line[*j] == '"' || line[*j] == '\'')
				is_quote(line, j, 1);
			if (line[*j])
				(*j)++;
		}
	}
	else
		return (1);
	return (0);
}

int	is_not_word(char *line, int *j)
{
	if (line[*j] == '$')
	{
		while (line[*j] && ft_isspace(line[*j]) == 0)
		{
			if (line[*j] == '\'' || line[*j] == '"')
				is_quote(line, j, 1);
			(*j)++;
		}
	}
	else if (!(ft_isalnum(line[*j] == 1) || ft_isspace(line[*j]) == 1
			|| line[*j] == '\0' || line[*j] == '/'))
	{
		while (!(ft_isalnum(line[*j] == 1) || ft_isspace(line[*j]) == 1
				|| line[*j] == '$' || line[*j] == '\0' || line[*j] == '/'))
			(*j)++;
	}
	else
		return (1);
	return (0);
}

void	check_pipes(t_init *init)
{
	t_list	*tmp;

	tmp = init->sentence;
	while (tmp)
	{
		if (tmp->word[0] == '|' && tmp->next->word[0] == '|')
		{
			printf("syntax error\n");
			return ;
		}
		tmp = tmp->next;
	}
	lexer(init);
}

void	cut_sentence(t_init *init, char *line, int *i, int j)
{
	int		spaces;
	t_list	*new;

	while (line[j])
	{
		j = *i;
		while (ft_isspace(line[j]) == 1)
				j++;
		spaces = j - *i;
		if (is_word(line, &j))
		{
			if (is_quote(line, &j, 1))
				is_not_word(line, &j);
		}
		*i += spaces;
		if (*i != j)
		{
			new = ft_lstnew(ft_substr(line, i, j - *i));
			if (!new)
				return ;
			ft_lstadd_back(&(init->sentence), new);
		}
	}
	check_pipes(init);
}
