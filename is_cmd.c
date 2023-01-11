/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:33:46 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/11 18:20:18 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

extern int	g_exit_code;

char	*get_access(char **path, char *cmd)
{
	int		i;
	int		acs;
	char	*right_path;

	acs = access(cmd, F_OK | X_OK);
	if (!path)
		return (ft_printf("%s: %s\n", cmd, strerror(ENOENT)), NULL);
	i = 0;
	acs = -1;
	while (path[i] && acs == -1)
	{
		right_path = ft_strjoin(path[i], cmd);
		if (!right_path)
			return (perror("right_path"), NULL);
		acs = access(right_path, F_OK | X_OK);
		if (acs < 0)
			free(right_path);
		i++;
	}
	if (acs < 0)
		return (ft_printf("%s: command not found\n", cmd), NULL);
	return (right_path);
}

void	is_cmd(t_lexer *tmp, t_init *init)
{
	printf("ici2\n");
	printf("%s\n", tmp->cmd);
	if (access(tmp->cmd, F_OK | X_OK) >= 0)
	{
		tmp->prog = ft_strdup(tmp->cmd);
		if (!tmp->prog)
		{
			free_before_exit(init);
			exit(0);
		}
	}
	else
	{	
		printf("ici3\n");
		tmp->prog = get_access(init->path, tmp->cmd);
	}
	if (!tmp->prog)
	{
		free_before_exit(init);
		g_exit_code = 127;
		exit(g_exit_code);
	}
}
