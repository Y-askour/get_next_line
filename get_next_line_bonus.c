/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 11:51:53 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/31 10:20:12 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <stdio.h>

int	read_from_fd(int fd, char **str)
{
	int		n_bytes;
	char	*tmp;

	*str = malloc(sizeof(char) * BUFFER_SIZE);
	n_bytes = read(fd,*str, BUFFER_SIZE);
	if (n_bytes <= 0)
	{
		free(*str);
		return (n_bytes);
	}
	if (n_bytes < BUFFER_SIZE)
	{
		str[0][n_bytes] = 0;
		tmp = ft_strdup(*str);
		free(*str);
		*str = tmp;
	}
	str[0][n_bytes] = 0;
	return (n_bytes);
}

char	*join_readed(int fd, char *str)
{
	int		n_bytes;
	char	*readed;
	char	*final_line;

	n_bytes = 1;
	final_line = str;
	while (n_bytes > 0)
	{
		n_bytes = read_from_fd(fd, &readed);
		if (n_bytes <= 0)
		{
			if (ft_strlen(final_line))
				return (final_line);
			free(str);
			return (NULL);
		}
		final_line = ft_strjoin(final_line, readed);
		if (check_new_line(final_line))
			break ;
	}
	return (final_line);
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
	char		*final_line;
	char		*old_remain[1024];
	static char	*remain[1024];

	if (fd < 0)
		return (NULL);
	if (fd > 1024)
		return (NULL);
	if (remain[fd])
		newline = ft_strdup(remain[fd]);
	else
		newline = ft_strdup("");
	newline = join_readed(fd, newline);
	final_line = new_line(newline);
	old_remain[fd] = remain[fd];
	remain[fd] = new_remain(newline);
	if (old_remain[fd])
		free(old_remain[fd]);
	return (final_line);
}
