/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customSplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:18:41 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/09 17:54:07 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char	*cust_strjoin(char *s1, char s2)
{
	char	*result;
	size_t	i;

	i = 0;
	result = malloc(ft_strlen(s1) + 2);
	if (!result)
		return (0);
	while (i < ft_strlen(s1))
	{
		result[i] = s1[i];
		i++;
	}
	result[i++] = s2;
	return (result[i] = 0, free(s1), result);
}

char	**custt_strjoin(char **s1, char *s2)
{
	char	**result;
	int		i;
	int		sz;

	sz = 0;
	if (!*s2)
		return (s1);
	while (s1[sz])
		sz++;
	result = malloc((sz + 2) * sizeof(char *));
	if (!result)
		return (0);
	i = -1;
	while (++i < sz)
		result[i] = s1[i];
	result[i++] = s2;
	result[i] = NULL;
	free(s1);
	return (result);
}

char	*func_helper(char *s, int flg, char chr_flg, int *i)
{
	char	*tmp;
	int		count;

	count = 0;
	tmp = ft_strdup("");
	while (s[*i])
	{
		if ((flg && s[*i] == chr_flg))
			count++;
		else if (!flg && is_whitespace(s[*i]))
		{
			(*i)++;
			break;
		}
		tmp = cust_strjoin(tmp, s[*i]);
		(*i)++;
		if (count == 2)
			break ;
	}
	return (tmp);
}

char	**cust_split(char *s)
{
	int		flg;
	char	**res;
	char	chr_flg;
	int		i;

	i = 0;
	res = malloc(sizeof(char *));
	res[0] = NULL;
	while (s[i])
	{
		flg = 0;
		chr_flg = 0;
		while (is_whitespace(s[i]))
			i++;
		if ((s[i] == '\'' || s[i] == '"') && (i - 1 < 0 || s[i - 1] != '\\'))
		{
			chr_flg = s[i];
			flg = 1;
		}
		if (!s[i])
			break ;
		res = custt_strjoin(res, func_helper(s, flg, chr_flg, &i));
	}
	return (res);
}
