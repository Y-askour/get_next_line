/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 11:51:53 by yaskour           #+#    #+#             */
/*   Updated: 2022/09/02 17:20:44 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <stdio.h>

int	loop_body(int n_bytes, char	**readed, char	**line)
{
	char	*tmp;

	if (n_bytes < BUFFER_SIZE)
	{
		readed[0][n_bytes] = 0;
		tmp = ft_strdup(readed[0]);
		free(readed[0]);
		readed[0] = tmp;
	}
	readed[0][n_bytes] = 0;
	line[0] = ft_strjoin(line[0], readed[0]);
	if (check_new_line(line[0]))
	{
		free(readed[0]);
		return (1);
	}
	return (0);
}

char	*read_and_join(int fd, char *remain)
{
	char	*readed;
	int		n_bytes;
	char	*line;

	if (remain)
		line = ft_strdup(remain);
	else
		line = ft_strdup("");
	readed = malloc(sizeof(char) * BUFFER_SIZE + 1);
	n_bytes = 1;
	while (n_bytes > 0)
	{
		n_bytes = read(fd, readed, BUFFER_SIZE);
		if (loop_body(n_bytes, &readed, &line))
			return (line);
	}
	if (ft_strlen(line))
	{
		free(readed);
		return (line);
	}
	free(line);
	free(readed);
	return (0);
}

char	*new_line(char *newline)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!new_line_loop(newline, &i))
		return (0);
	if (newline[i] == 0)
		return (newline);
	tmp = malloc(sizeof(char) * i + 2);
	i = 0;
	while (newline[i] && newline[i] != '\n')
	{
		tmp[i] = newline[i];
		i++;
	}
	if (newline[i] == '\n')
		tmp[i++] = '\n';
	tmp[i] = '\0';
	free(newline);
	return (tmp);
}

char	*new_remain(char *str)
{
	char	*remain;
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			break ;
		i++;
	}
	if (!str[i++])
		return (NULL);
	remain = ft_strdup(&str[i]);
	return (remain);
}

char	*get_next_line(int fd)
{
	char		*newline;
	static char	*remain;

	if (fd < 0 || !BUFFER_SIZE)
		return (NULL);
	newline = read_and_join(fd, remain);
	free(remain);
	remain = new_remain(newline);
	return (new_line(newline));
}
