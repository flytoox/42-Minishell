/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 00:34:32 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/30 03:28:49 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(int n)
{
	int	result;

	if (!n)
		return (1);
	result = 0;
	if (n < 0)
		result += 1;
	while (n != 0)
	{
		n /= 10;
		result++;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	int		nb;
	char	*s;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	nb = count(n);
	s = malloc(nb + 1);
	if (!s)
		return (0);
	garbg_add_back(&g_data.garbage, garbg_new(s));
	if (!n)
		s[0] = '0';
	if (n < 0)
	{
		s[0] = '-';
		n *= -1;
	}
	s[nb] = 0;
	while (n != 0)
	{
		s[--nb] = (n % 10) + 48;
		n /= 10;
	}
	return (s);
}
