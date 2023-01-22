/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:10:59 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/22 17:32:42 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

int	g_exit_code = 0;

char	*lst_env(t_init *init, char **envp)
{
	int		i;
	t_env	*new;

	i = 0;
	init->env = NULL;
	init->var = NULL;
	while (envp[i])
	{
		new = ft_envnew(NULL);
		if (!new)
			return (NULL);
		new->str = ft_strdup(envp[i]);
		if (!new->str)
			return (free(new), NULL);
		ft_envadd_back(&(init->env), new);
		i++;
	}
	return ("OK");
}

char	*init_struct(t_init *init)
{
	int		i;
	int		size;
	t_env	*first;

	i = 0;
	size = ft_envsize(init->env);
	first = init->env;
	init->nb_pipe = 0;
	init->sentence = NULL;
	init->lexer = NULL;
	init->envp = malloc(sizeof(char *) * (size + 1));
	if (!init->envp)
		return (NULL);
	while (i < size)
	{
		init->envp[i] = init->env->str;
		init->env = init->env->next;
		i++;
	}
	init->env = first;
	init->envp[i] = NULL;
	return ("ok");
}

void	minishell(t_init *init)
{
	char	*line;

	while (1)
	{
		if (!init_struct(init))
		{
			free_str(init->path);
			return (free_env(init));
		}
		init->path = get_path(init->envp);
		line = readline("$> ");
		if (!line)
			is_exit(init, init->lexer);
		parsing_line(line, init);
		if (ft_strlen(line))
			add_history(line);
		ft_dellist(&(init->sentence), &(init->lexer));
		if (init->nb_pipe)
			free_pipe(init);
		free(init->envp);
		if (init->path)
			free_str(init->path);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_init	init;

	(void)argv;
	if (argc == 1)
	{
		if (!(lst_env(&init, envp)))
			return (free_env(&init), 1);
		signal(SIGINT, &signal_int);
		signal(SIGQUIT, SIG_IGN);
		minishell(&init);
	}
	return (g_exit_code);
}
