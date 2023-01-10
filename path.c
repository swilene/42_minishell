/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:24:46 by saguesse          #+#    #+#             */
/*   Updated: 2022/11/21 12:19:56 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

char	**get_env(char **path)
{
	int		i;
	char	**path_name;

	i = 0;
	while (path[i])
		i++;
	path_name = malloc(sizeof(path_name) * (i + 1));
	if (!path_name)
		return (free_str(path), NULL);
	i = 0;
	while (path[i])
	{
		path_name[i] = ft_strjoin(path[i], "/");
		if (!path_name[i])
		{
			free_str(path_name);
			return (free_str(path), NULL);
		}
		free(path[i]);
		i++;
	}
	path_name[i] = NULL;
	free(path);
	return (path_name);
}

char	**get_path(char **envp)
{
	int		i;
	char	*paths;
	char	*find_path;
	char	**path;

	i = 0;
	find_path = NULL;
	while (envp[i] && find_path == NULL)
	{
		find_path = ft_strnstr(envp[i], "PATH=", 5);
		i++;
	}
	if (!find_path)
		return (NULL);
	i = 5;
	paths = ft_substr(find_path, &i, ft_strlen(find_path));
	if (!paths)
		return (NULL);
	path = ft_split(paths, ':');
	free(paths);
	if (!path)
		return (ft_printf("%s\n", strerror(ENOMEM)), NULL);
	return (get_env(path));
}
