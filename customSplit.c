/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customSplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:18:41 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/08 15:50:09 by obelaizi         ###   ########.fr       */
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
	remove_quotes(s2);
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

char	*func_helper(char **s, int flg, char chr_flg)
{
	char	*tmp;

	tmp = ft_strdup("");
	while (**s)
	{
		if ((flg && **s == chr_flg) || (!flg && is_whitespace(**s)))
		{
			flg = 0;
			(*s)++;
			break ;
		}
		tmp = cust_strjoin(tmp, **s);
		(*s)++;
	}
	return (tmp);
}

char	**cust_split(char *s)
{
	int		flg;
	char	**res;
	char	chr_flg;

	flg = 0;
	chr_flg = 0;
	res = malloc(sizeof(char *));
	res[0] = NULL;
	while (*s)
	{
		while (is_whitespace(*s))
			s++;
		if (*s == '\'' || *s == '\"')
		{
			chr_flg = *s;
			flg = 1;
			s++;
		}
		if (!*s)
			break ;
		res = custt_strjoin(res, func_helper(&s, flg, chr_flg));
	}
	return (res);
}
