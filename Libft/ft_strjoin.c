/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 00:39:06 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/31 01:39:21 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, const char *s2)
{
	char	*result;
	size_t	size;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(size + 1);
	if (!result)
		return (0);
	garbg_add_back(&g_data.garbage, garbg_new(result));
	while (i < size)
	{
		while (i < ft_strlen(s1))
		{
			result[i] = s1[i];
			i++;
		}
		if (!(*s2))
			break ;
		result[i++] = *s2++;
	}
	return (result[i] = 0, result);
}
