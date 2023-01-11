/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:18:39 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/11 12:32:01 by saguesse         ###   ########.fr       */
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
		if (tmp->cmd || tmp->program)
		{
			waitpid(tmp->pid, &wstatus, 0);
			if (WIFEXITED(wstatus))
				g_exit_code = WEXITSTATUS(wstatus);
		}
		tmp = tmp->next;
	}
}
