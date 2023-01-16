/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:18:39 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/16 15:24:04 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

extern int	g_exit_code;

void	parent_proc(t_init *init)
{
	int		wstatus;
	t_lexer	*tmp;

	close_fd_pipe(init);
	close_files(init);
	tmp = init->lexer;
	while (tmp)
	{
		if (!tmp->cmd && !tmp->builtin && !tmp->program)
			;
		else if (init->nb_pipe || tmp->cmd || tmp->program)
		{
			waitpid(tmp->pid, &wstatus, 0);
			if (WTERMSIG(wstatus) == 2)
				printf("\n");
			else if (WTERMSIG(wstatus) == 3)
				printf("Quit (core dumped)\n");
			if (WIFEXITED(wstatus))
				g_exit_code = WEXITSTATUS(wstatus);
		}
		tmp = tmp->next;
	}
}
