/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 13:07:15 by yaskour           #+#    #+#             */
/*   Updated: 2021/11/21 20:11:19 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <string.h>


size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	int			j;
	size_t		dst_len;
	size_t		src_len;

	i = ft_strlen(dst);
	j = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size < dst_len + 1)
		return (src_len + size);
	if (size > dst_len + 1)
	{
		while (*(src + j) && i < size - 1)
			*(dst + i++) = *(src + j++);
	}
	*(dst + i) = '\0';
	return (dst_len + src_len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str1;
	char	*str2;
	int		len;
	char	*ptr;

	str1 = (char *)s1;
	str2 = (char *)s2;
	if (!s1 || !s2)
		return (NULL);
	len = strlen(str1) + strlen(str2);
	ptr = malloc(sizeof(char) * len + 1);
	if (!ptr)
		return (NULL);
	while (*str1)
		*ptr++ = *str1++;
	while (*str2)
		*ptr++ = *str2++;
	*ptr = '\0';
	return ((char *) ptr - len);
}


size_t	ft_strlen( const char *theString )
{
	unsigned int	i;

	i = 0;
	while (*theString++)
		i++;
	return (i);
}


char	*ft_strdup(const char *s1)
{
	int		len;
	char	*ptr;
	int		i;

	i = 0;
	len = ft_strlen(s1);
	ptr = malloc(sizeof(char) * len + 1);
	if (ptr == NULL)
		return (ptr);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	size;

	i = 0;
	size = (int)ft_strlen(s) + 1;
	while (i < size)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
		i++;
	}
	return (NULL);
}


static char	*ft_alloc(char *src, char c)
{
	size_t	len;
	char	*dest;

	len = 0;
	while (src[len] && src[len] != c)
		len++;
	dest = malloc(sizeof(char) * len + 1);
	if (dest == NULL)
		return (NULL);
	len = 0;
	while (src[len] && src[len] != c)
	{
		dest[len] = src[len];
		len++;
	}
	dest[len] = 0;
	return (dest);
}

static size_t	count_words(char const *str, char c)
{
	size_t	words;

	words = 0;
	while (*str)
	{
		if (*str != c)
		{
			words++;
			while (*str && *str != c)
				str++;
			continue ;
		}
		str++;
	}
	return (words);
}

static int	ft_check_is_alloc(char **str, int j)
{
	if (str[j] == NULL)
	{
		while (j)
			free(str[--j]);
		free(str);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	words;
	size_t	w;

	w = 0;
	if (!s)
		return (NULL);
	words = count_words(s, c);
	ptr = (char **)malloc(sizeof(char *) * words + 1);
	if (ptr == NULL)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			ptr[w] = ft_alloc((char *) s, c);
			if (!(ft_check_is_alloc(ptr, w++)))
				return (NULL);
			while (*(s + 1) && *(s + 1) != c)
				s++;
		}
		s++;
	}
	ptr[w] = NULL;
	return (ptr);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	srclen;
	size_t	i;

	i = 0;
	srclen = 0;
	while (src[srclen])
		srclen++;
	if (size == 0)
		return (srclen);
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (srclen);
}
