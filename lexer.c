/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:48:30 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/20 18:01:44 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

void	free_new_lexer(t_lexer *new)
{
	if (new->cmd)
		free(new->cmd);
	if (new->builtin)
		free(new->builtin);
	if (new->program)
		free(new->program);
	if (new->args)
		free_str(new->args);
	free(new);
}

void	lexer(t_init *init)
{
	t_list	*tmp;
	t_lexer	*new;

	is_env_var(init->sentence, init);
	split_word(init->sentence);
	tmp = init->sentence;
	new = ft_lexernew();
	if (!new)
		return ;
	while (tmp)
	{
		if (tmp->word[0] == '#')
			break ;
		if (tmp->word[0] == '<' || tmp->word[0] == '>')
		{
			if (!(is_redirection(new, &tmp)))
				return (free_new_lexer(new));
		}
		else if (ft_isalnum(tmp->word[0]) == 1 || tmp->word[0] == '/'
			|| tmp->word[0] == '$' || tmp->word[0] == '\'')
		{	
			if (!(check_builtin(tmp->word)))
			{
				if (!(check_envariables(tmp->word, init)))
				{
					new->cmd = ft_strdup(tmp->word);
					if (!new->cmd)
						return (free_new_lexer(new));
					if (!take_args(&tmp, new, 0, 0))
						return (free_new_lexer(new));
				}
				else
					return (free_new_lexer(new));
			}
			else
			{
				new->builtin = ft_strdup(tmp->word);
				if (!new->builtin)
					return (free_new_lexer(new));
				if (!take_args(&tmp, new, 0, 0))
					return (free_new_lexer(new));
			}
		}
		else if (tmp->word[0] == '|')
		{
			new = is_pipe(tmp, new, init);
			if (!new)
				return ;
		}
		else if (tmp->word[0] == '.' && tmp->word[1] == '/')
		{
			new->program = ft_strdup(tmp->word);
			if (!new->program)
				return (free_new_lexer(new));
			if (!take_args(&tmp, new, 0, 0))
				return (free_new_lexer(new));
		}
		if (tmp)
			tmp = tmp->next;
	}
	ft_lexeradd_back(&(init->lexer), new);
	if (!init_files(init))
		return ;
	pipex(init);
}
