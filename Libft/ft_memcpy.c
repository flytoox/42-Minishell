/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:27:43 by obelaizi          #+#    #+#             */
/*   Updated: 2022/11/02 13:01:53 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *d, const void *s, size_t n)
{
	size_t	i;
	char	*dest;
	char	*src;

	src = (char *)s;
	dest = (char *)d;
	if (!src && !dest)
		return (0);
	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (d);
}
