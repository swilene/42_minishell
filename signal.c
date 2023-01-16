/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:37:20 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/16 16:22:55 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <prototypes.h>

extern int	g_exit_code;

void	signal_int(int signal)
{
	g_exit_code = 130;
	if (signal == SIGINT)
	{
		printf("\n");
	//	dprintf(2, "1\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_heredoc(int signal)
{

	printf("\n");
	//dprintf(2, "2\n");
	g_exit_code = 130;
	if (signal == SIGINT)
		close(0);
}

void	signal_fork(int signal)
{
	//dprintf(2, "3\n");
	if (signal == SIGINT)
		g_exit_code = 130;
	else if (signal == SIGQUIT)
		g_exit_code = 131;

}
