/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functionsHelpers1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:43:34 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/09 15:53:41 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_str(const char *s, const char *s1)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (!ft_strncmp(s, s1, ft_strlen(s1)))
			count++;
		s++;
	}
	return (count);
}

int	count_char(const char *s, char c)
{
	int	count;
	int	i;

	i = -1;
	count = 0;
	while (s[++i])
	{
		if (s[i] == c && (i - 1 < 0 || s[i - 1] != '\\'))
			count++;
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
