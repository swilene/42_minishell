/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:24:16 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/23 15:14:07 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

extern int	g_exit_code;

int	multiple_arg(char *str, int pipe)
{
	if (str_isdigit(str) == 0)
	{
		g_exit_code = 1;
		if (pipe == 0)
			printf("exit\n");
		write(1, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	else
	{
		g_exit_code = 2;
		if (pipe == 0)
			printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", str);
		return (0);
	}
}

int	single_arg(char *str, int pipe)
{
	int	arg;

	if (str_isdigit(str) == 0)
	{
		arg = atoi(str);
		if (arg < 0 || arg > 255)
			g_exit_code = 42;
		else
			g_exit_code = arg;
		if (pipe == 0)
			printf("exit\n");
	}
	else
	{
		g_exit_code = 2;
		if (pipe == 0)
			printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", str);
	}
	return (0);
}

void	free_and_exit(t_init *init)
{
	free_env(init);
	free_var(init);
	if (init->path)
		free_str(init->path);
	if (init->nb_pipe)
		free_pipe(init);
	if (init->envp)
		free(init->envp);
	ft_dellist(&(init->sentence), &(init->lexer));
	rl_clear_history();
	exit(g_exit_code);
}

void	is_exit(t_init *init, t_lexer *lexer)
{
	int	i;
	int	leave;

	i = 0;
	leave = 0;
	if (!lexer)
		free_and_exit(init);
	while (lexer->args[i])
		i++;
	if (i > 2)
		leave = multiple_arg(lexer->args[1], init->nb_pipe);
	else if (i > 1)
		leave = single_arg(lexer->args[1], init->nb_pipe);
	if (leave == 0)
		free_and_exit(init);
}
