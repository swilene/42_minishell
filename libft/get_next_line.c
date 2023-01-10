/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 09:52:23 by saguesse          #+#    #+#             */
/*   Updated: 2022/10/27 17:35:09 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	write_buf(char *line, char *buf)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	while (line[i])
	{
		buf[j] = line[i];
		line[i] = '\0';
		i++;
		j++;
	}
}

char	*ft_strjoin_gnl(char *line, char *buf, int ret)
{
	int		i;
	int		j;
	char	*str;

	if (line == NULL)
		return (buf);
	i = ft_strlen(line);
	j = 0;
	str = (char *)malloc(sizeof(*str) * (i + ret) + 1);
	if (!str)
		return (NULL);
	while (line[j])
	{
		str[j] = line[j];
		j++;
	}
	j = 0;
	while (buf[j])
	{
		str[i + j] = buf[j];
		j++;
	}
	str[i + j] = '\0';
	free(line);
	return (str);
}

int	ft_read_fd(int fd, char **l, char *buf, int buffer_size)
{
	int		ret;
	char	*line;

	line = *l;
	ret = read(fd, buf, buffer_size);
	if (ret == -1)
		return (1);
	if (ret == 0)
		return (2);
	buf[ret] = '\0';
	if (line == NULL)
	{
		line = ft_strdup(buf);
		if (line == NULL)
			return (1);
	}
	else
	{
		line = ft_strjoin_gnl(line, buf, ret);
		if (line == NULL)
			return (1);
	}
	*l = line;
	return (0);
}

char	*get_next_line(int fd)
{
	int			buffer_size;
	static char	buf[4096];
	char		*line;
	int			i;

	buffer_size = 4096;
	i = 0;
	line = NULL;
	if (*buf)
	{
		line = ft_strdup(buf);
		if (line == NULL)
			return (NULL);
	}
	while (ft_strchr(buf, '\n') == NULL && i == 0)
		i = ft_read_fd(fd, &line, buf, buffer_size);
	if (i == 1)
		return (NULL);
	ft_bzero(buf, buffer_size);
	if (i == 0)
		write_buf(line, buf);
	return (line);
}
