/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:26:32 by obelaizi          #+#    #+#             */
/*   Updated: 2022/11/02 10:42:15 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*s;

	if (count != 0 && count * size / count != size)
		return (NULL);
	s = malloc(count * size);
	if (!s)
		return (0);
	ft_memset(s, 0, count * size);
	return (s);
}
