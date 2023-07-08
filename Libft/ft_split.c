/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 02:39:00 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/08 16:46:44 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip_c(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	return (i);
}

void	free_dbl_pntr(void **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static int	count_words(char const *s, char c, int *i)
{
	int	total;

	total = 1;
	*i = 0;
	while (*s && *s == c)
		s++;
	if (!(*s))
		return (0);
	while (*s)
	{
		if (*s == c && *(s + 1) && *(s + 1) != c)
			total++;
		s++;
	}
	return (total);
}

static int	word_size(const char *s, char c)
{
	int	size;

	size = 0;
	while (*s && *s != c)
	{
		size++;
		s++;
	}
	return (size);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		words;
	char	**str;
	int		j;

	if (!s)
		return (0);
	words = count_words(s, c, &i);
	str = malloc(sizeof(char *) * (words + 1));
	if (!str)
		return (0);
	while (*s && i < words)
	{
		j = 0;
		s = skip_c(s, c) + s;
		str[i] = malloc(word_size(s, c) + 1);
		if (!str[i])
			return (free_dbl_pntr((void **)str), NULL);
		while (*s && *s != c)
			str[i][j++] = *(s)++;
		str[i++][j] = 0;
		if (*s)
			s++;
	}
	return (str[i] = 0, str);
}
