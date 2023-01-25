/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:48:30 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/25 15:00:23 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

int	builtin_command_envariable(t_list **tmp, t_init *init, t_lexer *new)
{
	if (!(check_builtin((*tmp)->word)))
	{
		if (!(check_envariables((*tmp)->word, init)))
		{
			new->cmd = ft_strdup((*tmp)->word);
			if (!new->cmd)
				return (free_new_lexer(new), 1);
			if (!take_args(tmp, new, 0, 0))
				return (free_new_lexer(new), 2);
		}
		else
			return (free_new_lexer(new), 3);
	}
	else
	{
		new->builtin = ft_strdup((*tmp)->word);
		if (!new->builtin)
			return (free_new_lexer(new), 4);
		if (!take_args(tmp, new, 0, 0))
			return (free_new_lexer(new), 5);
	}
	return (0);
}

int	lexer_program(t_list **tmp, t_lexer *new)
{
	new->program = ft_strdup((*tmp)->word);
	if (!new->program)
		return (free_new_lexer(new), 1);
	if (!take_args(tmp, new, 0, 0))
		return (free_new_lexer(new), 2);
	return (0);
}

static int	parsing_word(t_list **tmp, t_init *init, t_lexer **new)
{
	if ((*tmp)->word[0] == '<' || (*tmp)->word[0] == '>')
	{
		if (!(is_redirection(*new, tmp)))
			return (free_new_lexer(*new), 1);
	}
	else if (ft_isalnum((*tmp)->word[0]) == 1 || ft_isspace((*tmp)->word[0])
		== 1 || (*tmp)->word[0] == '/' || (*tmp)->word[0] == '$'
		|| (*tmp)->word[0] == '\'')
	{
		if (builtin_command_envariable(tmp, init, *new))
			return (2);
	}
	else if ((*tmp)->word[0] == '|')
	{
		*new = is_pipe(*tmp, new, init);
		if (!*new)
			return (3);
	}
	else if ((*tmp)->word[0] == '.' && (*tmp)->word[1] == '/')
	{
		if (lexer_program(tmp, *new))
			return (4);
	}
	return (0);
}

void	lexer(t_init *init)
{
	t_list	*tmp;
	t_lexer	*new;

	if (env_var(init->sentence, init, 0))
		return ;
	if (split_word(init->sentence))
		return ;
	tmp = init->sentence;
	new = ft_lexernew();
	if (!new)
		return ;
	while (tmp)
	{
		//printf("DEBUG word: %s\n", tmp->word);
		if (tmp->word[0] == '#')
			break ;
		if (parsing_word(&tmp, init, &new))
			return ;
		if (tmp)
			tmp = tmp->next;
	}
	ft_lexeradd_back(&(init->lexer), new);
	if (!init_files(init))
		return ;
	pipex(init);
}
