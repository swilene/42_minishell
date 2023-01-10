/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:37:20 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/10 17:14:38 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <prototypes.h>

void	signal_int(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_heredoc(int signal)
{
	if (signal == SIGINT)
		close(0);
}
