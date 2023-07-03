/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 00:39:06 by obelaizi          #+#    #+#             */
/*   Updated: 2022/11/05 21:12:09 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	size;
	size_t	i;
	int		j;

	if (!s1 || !s2)
		return (0);
	i = 0;
	j = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(size + 1);
	if (!result)
		return (0);
	while (i < size)
	{
		while (i < ft_strlen(s1))
		{
			result[i] = s1[i];
			i++;
		}
		if (!(*s2))
			break ;
		result[i++] = s2[j++];
	}
	return (result[i] = 0, result);
}
