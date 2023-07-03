/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 02:39:00 by obelaizi          #+#    #+#             */
/*   Updated: 2022/11/03 13:54:26 by obelaizi         ###   ########.fr       */
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

static void	free_str(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
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
			return (free_str(str, i), NULL);
		while (*s && *s != c)
			str[i][j++] = *(s)++;
		str[i++][j] = 0;
		if (*s)
			s++;
	}
	return (str[i] = 0, str);
}
