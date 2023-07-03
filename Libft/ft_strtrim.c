/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:40:36 by obelaizi          #+#    #+#             */
/*   Updated: 2022/11/03 13:55:02 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(const char *s, int c)
{
	while (*s)
	{
		if (c == *s)
			return (1);
		s++;
	}
	return (0);
}

static int	check_first(const char *s, const char *finder)
{
	int	i;

	i = 0;
	while (s[i] && check(finder, s[i]))
		i++;
	return (i);
}

static int	check_last(const char *s, const char *finder)
{
	size_t	i;
	int		count;

	count = 0;
	i = ft_strlen(s) - 1;
	while (s[i] && check(finder, s[i]))
	{
		count++;
		i--;
	}
	return (count);
}

char	*ft_strtrim(char const *s, char const *finder)
{
	int			last;
	char		*result;
	size_t		first;

	if (!s || !finder)
		return (0);
	if (!(*s))
		return (result = ft_strdup(""));
	first = check_first(s, finder);
	if (first == ft_strlen(s))
		return (result = ft_strdup(""));
	last = check_last(s, finder);
	return (result = ft_substr(s, first, ft_strlen(s) - last - first));
}
