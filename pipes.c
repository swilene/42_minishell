/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:49:31 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/11 18:13:45 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

int	init_fd_pipe(t_init *init)
{
	int	i;

	init->fd_pipe = malloc(sizeof(init->fd_pipe) * init->nb_pipe);
	if (!init->fd_pipe)
		return (perror("fd_pipe"), 1);
	i = 0;
	while (i < init->nb_pipe)
	{
		init->fd_pipe[i] = malloc(sizeof(init->fd_pipe[i]) * 2);
		if (!init->fd_pipe[i])
			return (perror("fd_pipe"), 2);
		i++;
	}
	i = 0;
	while (i < init->nb_pipe)
	{
		if (pipe(init->fd_pipe[i]) < 0)
			return (3);
		i++;
	}
	return (0);
}

int	pipex(t_init *init)
{
	int		i;
	t_lexer	*tmp;

	if (init->nb_pipe)
	{
		if (init_fd_pipe(init))
			return (1);
	}
	tmp = init->lexer;
	i = 0;
	while (tmp)
	{
		if (tmp->cmd || tmp->program)
		{
			tmp->pid = fork();
			if (tmp->pid < 0)
				return (perror("fork()"), 3);
			if (tmp->pid == 0)
			{
				/*if (tmp->cmd)
				{
					printf("%s\n", tmp->cmd);
				}*/
				signal(SIGINT, &signal_block_cmd);
				//if (tmp->cmd) --> signal
				//else --> pas signal
				do_dup(tmp, init, i);
			}
		}
		else
			do_dup(tmp, init, i);
		i++;
		tmp = tmp->next;
	}
	parent_proc(init);
	return (0);
}

t_lexer	*is_pipe(t_list *tmp, t_lexer *new, t_init *init, char *word)
{
	if (ft_strlen(tmp->word) > 1)
	{
		free_new_lexer(new, word);
		return (printf("syntax error\n"), NULL);
	}
	ft_lexeradd_back(&(init->lexer), new);
	new = ft_lexernew();
	if (!new)
		return (free(word), NULL);
	init->nb_pipe++;
	return (new);
}
