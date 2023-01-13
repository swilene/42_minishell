/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:45:23 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/13 10:53:30 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

void	execution(t_lexer *lexer, t_init *init, int i)
{
	if (lexer->builtin)
	{
		if (ft_strcmp(lexer->builtin, "pwd") == 0)
			is_pwd(init, lexer, i);
		else if (ft_strcmp(lexer->builtin, "env") == 0)
			is_env(init, lexer, i);
		else if (ft_strcmp(lexer->builtin, "export") == 0)
			is_export(init, &(init->env), &(init->var));
		else if (ft_strcmp(lexer->builtin, "unset") == 0)
			is_unset(init, &(init->env), &(init->var));
		else if (ft_strcmp(lexer->builtin, "echo") == 0)
		{
			if (lexer->env_var)
				is_echo_var(init, lexer, i);
			else
				is_echo(init, lexer, i);
		}
		else if (ft_strcmp(lexer->builtin, "cd") == 0)
			is_cd(lexer);
		else if (ft_strcmp(lexer->builtin, "exit") == 0)
			is_exit(init);
	}
	if (init->nb_pipe)
	{
		free_before_exit(init);
		exit(0);
	}
}
