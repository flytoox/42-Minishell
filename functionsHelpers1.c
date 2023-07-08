/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functionsHelpers1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:43:34 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/08 21:54:06 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_str(const char *s, const char *s1)
{
	int	count;
	int	i;

	count = 0;
	while (*s)
	{
		i = 1;
		if (*s == *s1)
		{
			i = -1;
			while (s1[++i])
				if (s1[i] != s[i])
					break ;
			if (!s1[i])
				count++;
		}
		s += i;
	}
	return (count);
}

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	new_ptr = malloc(size);
	if (!new_ptr)
		exit (1);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}

// char	*expand(char **splts)
// {
// 	int	i;

// 	i = -1;
// 	while (splts[++i])
// 	{
// 	}
// }
