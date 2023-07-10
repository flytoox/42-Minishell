/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functionsHelpers1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:43:34 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/09 19:01:25 by obelaizi         ###   ########.fr       */
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

int	is_closed(const char *s)
{
	int		flg;
	char	flg_c;
	int		i;

	i = -1;
	flg = 0;
	flg_c = 0;
	while (s[++i])
	{
		if (flg && s[i] == flg_c)
		{
			flg = 0;
			i++;
		}
		if (s[i] && (s[i] == '"' || s[i] == '\'') && !flg)
		{
			flg = 1;
			flg_c = s[i];
		}
	}
	return (flg);
}

// char	*expand(char **splts)
// {
// 	int	i;

// 	i = -1;
// 	while (splts[++i])
// 	{
// 	}
// }
