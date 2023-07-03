/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:03:39 by obelaizi          #+#    #+#             */
/*   Updated: 2022/11/02 10:45:55 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int x, size_t n)
{
	size_t			index;
	unsigned char	*s;

	s = (unsigned char *)str;
	index = 0;
	while (index < n)
	{
		s[index] = (unsigned char)x;
		index++;
	}
	return (str);
}
