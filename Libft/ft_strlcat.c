/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:35:26 by obelaizi          #+#    #+#             */
/*   Updated: 2022/11/02 18:31:26 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d;
	size_t	i;
	size_t	dst_size;

	if (!size)
		return (ft_strlen(src));
	d = ft_strlen(dst);
	dst_size = d;
	i = 0;
	if (size <= d)
		return (ft_strlen(src) + size);
	while (src[i] && i < size - dst_size - 1)
	{
		dst[d] = src[i];
		d++;
		i++;
	}
	dst[d] = 0;
	return (ft_strlen(src) + dst_size);
}
