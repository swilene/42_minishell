/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:48:30 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/10 11:47:04 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

void	free_new_lexer(t_lexer *new, char *word)
{
	if (word)
		free(word);
	if (new->quotes)
		free_str(new->quotes);
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
	char	*word;

	tmp = init->sentence;
	new = ft_lexernew();
	if (!new)
		return ;
	if (!take_quotes(tmp, new, 0, 0))
		return (free(new));
	while (tmp)
	{
		if (tmp->word[0] == '#')
			break ;
		word = remove_quotes(tmp->word, 0, 0);
		if (!word)
			return (free_new_lexer(new, word));
		if (word[0] == '<' || word[0] == '>')
		{
			if (!(is_redirection(new, &tmp)))
				return (free_new_lexer(new, word));
		}
		else if ((word[0] >= 'a' && word[0] <= 'z') || (word[0]
				>= 'A' && word[0] <= 'Z'))
		{	
			if (!(check_builtin(word)))
			{
				if (!(check_envariables(word, init)))
				{
					new->cmd = ft_strdup(word);
					if (!new->cmd)
						return (free_new_lexer(new, word));
					if (!take_args(&tmp, new, 0, 0))
						return (free_new_lexer(new, word));
				}
				else
					return (free_new_lexer(new, word));
			}
			else
			{
				new->builtin = ft_strdup(word);
				if (!new->builtin)
					return (free_new_lexer(new, word));
				free(word);
				word = NULL;
				if (!take_args(&tmp, new, 0, 0))
					return (free_new_lexer(new, word));
			}
		}
		else if (word[0] == '$' && !new->env_var)
		{
			if (!is_env_var(init, word, new))
				return (free_new_lexer(new, word));
		}
		else if (word[0] == '|')
		{
			new = is_pipe(tmp, new, init, word);
			if (!new)
				return ;
			if (!take_quotes(tmp->next, new, 0, 0))
				return (free(new));
		}
		else if (word[0] == '.' && word[1] == '/')
		{
			new->program = ft_strdup(word);
			if (!new->program)
				return (free_new_lexer(new, word));
			if (!take_args(&tmp, new, 0, 0))
				return (free_new_lexer(new, word));
		}
		free(word);
		if (tmp)
			tmp = tmp->next;
	}
	ft_lexeradd_back(&(init->lexer), new);
	if (!init_files(init))
		return ;
	pipex(init);
}
