/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:41:18 by obelaizi          #+#    #+#             */
/*   Updated: 2023/01/18 12:55:34 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_char(char *s, char c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (c == *s)
			return (1);
		s++;
	}
	return (0);
}

int	handle_error(char *rest, int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (1);
	if (read(fd, NULL, 0) < 0)
	{
		if (rest)
			free(rest);
		rest = NULL;
		return (1);
	}
	return (0);
}

char	*fill(char *src)
{
	int		i;
	char	*dst;
	int		j;

	j = 0;
	i = 0;
	while (src[i] && src[i] != '\n')
		i++;
	if (src[i] == '\n')
		i++;
	dst = malloc(i + 1);
	if (!dst)
		return (free(src), NULL);
	dst[i] = 0;
	while (i--)
		dst[j++] = *(src++);
	return (dst);
}
