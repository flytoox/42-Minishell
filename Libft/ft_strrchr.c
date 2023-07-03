/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 13:56:06 by obelaizi          #+#    #+#             */
/*   Updated: 2022/11/04 11:42:52 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	len;

	len = (int)ft_strlen(str);
	while (len >= 0)
	{
		if ((char)c == str[len])
			break ;
		len--;
	}
	if (len != -1)
		return ((char *)str + len);
	return (0);
}
