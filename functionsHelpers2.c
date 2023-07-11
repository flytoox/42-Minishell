/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functionsHelpers2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 01:25:51 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/11 01:37:30 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bool	is_error(char *s, int i)
// {
// 	// return ((s[i] == '|' && s[i + 1] && s[i + 1] == '|') 
// 	// 		s[i] == '|' && s[i + 1] && s[i + 1] == '|')
// }

int	syntax_error(char *s)
{
	int		i;
	int		flg;

	flg = 0;
	if (s[0] == '|' || s[ft_strlen(s) - 1] == '|')
		return (1);
	i = -1;
	while (s[++i])
	{
		if ((s[i] == '"' || s[i] == '\'') && !flg)
			flg = i + 1;
		else if (flg && s[i] == s[flg - 1])
			flg = 0;
		else if (!flg && s[i] == '|' && s[i + 1] && s[i + 1] == '|')
			return (1);
	}
	return (258);
}