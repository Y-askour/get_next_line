/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:29:22 by yaskour           #+#    #+#             */
/*   Updated: 2021/11/22 18:38:12 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:33:47 by yaskour           #+#    #+#             */
/*   Updated: 2021/11/22 18:14:00 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 08:23:42 by yaskour           #+#    #+#             */
/*   Updated: 2021/11/22 17:33:36 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <string.h>
#include <stdio.h>


char *get_line(int fd,char **rest,char *line)
{
	char temp_data[BUFFER_SIZE + 1];
	read(fd,temp_data,BUFFER_SIZE);
	temp_data[BUFFER_SIZE] = 0;
	char *temp = NULL;
	size_t i;
	
	i = 0;
	if (*rest)
		ft_strjoin(line,*rest);
	*rest = ft_strdup("");
	while (!ft_strchr(temp_data,'\n'))
	{
		line = ft_strjoin(line,temp_data);
		read(fd,temp_data,BUFFER_SIZE);
	}
	if (ft_strchr(temp_data,'\n'))
	{
		int index = ft_strchr(temp_data,'\n') - temp_data;
		temp = malloc(ft_strlen(line) + (index) + 2);
		temp = ft_strdup(line);
		while(temp_data[i] != '\n')
		{
			temp[ft_strlen(line) + i] = temp_data[i];
			i++;
		}
		temp[ft_strlen(line) + i++] = '\n';
		temp[ft_strlen(line) + i] = '\0';
		ft_strlcpy(*rest,&temp_data[index + 1],ft_strlen(temp_data));
	}
	return (temp);
}

char *get_next_line(int fd)
{
	char *line;
	static char *rest;

	line = ft_strdup("");
	line = get_line(fd,&rest,line);
	return (line);
}
