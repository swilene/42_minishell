/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:59:09 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/13 15:43:32 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

extern int	g_exit_code;

void	wait_limiter(t_lexer *tmp, char *limiter, t_init *init)
{
	char	*line;

	signal(SIGINT, &signal_heredoc);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			printf("warning: here-document delimited by end-of-file\n");
			break ;
		}
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		write(tmp->fd_heredoc[1], line, ft_strlen(line));
		write(tmp->fd_heredoc[1], "\n", 1);
		free(line);
	}
	//close_fd_heredoc(tmp);
	//init->nb_pipe = 0;
	free_before_exit(init);
	exit(g_exit_code);
}

int	is_heredoc(t_red *tmp_red, t_lexer *tmp_lexer, t_init *init)
{
	int	pid;

	if (!tmp_red->file)
	{
		g_exit_code = 2;
		return (printf("syntax error\n"), 1);
	}
	tmp_lexer->heredoc = "heredoc";
	if (pipe(tmp_lexer->fd_heredoc) < 0)
		return (perror("pipe"), 2);
	pid = fork();
	if (pid < 0)
		return (close_fd_heredoc(tmp_lexer), 3);
	if (pid == 0)
		wait_limiter(tmp_lexer, tmp_red->file, init);
	waitpid(pid, NULL, 0);
	if (close(tmp_lexer->fd_heredoc[1]) < 0)
		perror("heredoc[1]");
	if (!tmp_lexer->cmd && !tmp_lexer->builtin)
	{
		if (close(tmp_lexer->fd_heredoc[0]) < 0)
			perror("heredoc[0]");
	}
	return (0);
}
