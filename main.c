/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 08:24:15 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/31 11:19:07 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include "ft_ansi.h"
#include <stdio.h>

int	main(void)
{
	int	fd;
	int	i;

	printf("BUFFER_SIZE = %d", BUFFER_SIZE);
	fd = open("test.txt", O_RDWR);
	if (fd < 0)
	{
		printf(ANSI_F_RED "Error opening \n");
		return (0);
	}
	i = 0;
	printf(ANSI_F_YELLOW "\nReading Lines...\n" ANSI_RESET);
	while (i < 10)
		printf(ANSI_F_CYAN "line :%d " ANSI_F_MAGENTA "\tstring :%s"
			ANSI_F_CYAN "\n", i++, get_next_line(fd));
}
