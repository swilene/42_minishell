/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:27:02 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/22 17:04:47 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

void	free_new_lexer(t_lexer *new)
{
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

void	free_var(t_init *init)
{
	t_env	*tmp;
	t_env	*var;

	var = init->var;
	while (var)
	{
		tmp = var->next;
		free(var->str);
		free(var);
		var = tmp;
	}
	var = NULL;
}

void	free_env(t_init *init)
{
	t_env	*tmp;
	t_env	*env;

	env = init->env;
	while (env)
	{
		tmp = env->next;
		free(env->str);
		free(env);
		env = tmp;
	}
	env = NULL;
}

void	free_pipe(t_init *init)
{
	int	i;

	i = 0;
	if (!init->fd_pipe)
		return ;
	while (i < init->nb_pipe)
	{
		if (init->fd_pipe[i])
			free(init->fd_pipe[i]);
		i++;
	}
	free(init->fd_pipe);
}
