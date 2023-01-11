/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:37:20 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/11 12:23:47 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <prototypes.h>

extern int	g_exit_code;

void	signal_int(int signal)
{
	g_exit_code = 130;
	if (signal == SIGINT)
	{
		printf("ici\n");
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_heredoc(int signal)
{
	g_exit_code = 130;
	if (signal == SIGINT)
		close(0);
}

void	signal_block_cmd(int signal)
{
	g_exit_code = 130;
	if (signal == SIGINT)
	{
		printf("\n");
		exit(130);
	}
}
