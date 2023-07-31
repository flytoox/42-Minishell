/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customSplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:18:41 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/31 00:35:23 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		exit (1);
	garbg_add_back(&g_data.garbage, garbg_new(result));
	while (i < ft_strlen(s1))
	{
		result[i] = s1[i];
		i++;
	}
	result[i++] = s2;
	return (result[i] = 0, result);
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
		exit (1);
	garbg_add_back(&g_data.garbage, garbg_new(result));
	i = -1;
	while (++i < sz)
		result[i] = s1[i];
	result[i++] = s2;
	result[i] = NULL;
	return (result);
}

char	*func_helper(char *s, int flg, char chr_flg, int *i)
{
	char	*tmp;

	tmp = ft_strdup("");
	tmp = cust_strjoin(tmp, s[*i]);
	(*i)++;
	while (s[*i])
	{
		if (!flg && (s[*i] == '"' || s[*i] == '\''))
		{
			chr_flg = s[*i];
			flg = 1;
		}
		else if ((flg && s[*i] == chr_flg))
			flg = 0;
		if (!flg && is_whitespace(s[*i]))
		{
			(*i)++;
			break ;
		}
		tmp = cust_strjoin(tmp, s[*i]);
		(*i)++;
	}
	return (tmp);
}

void	cust_split(char *s, t_cmd **cmds)
{
	int		flg;
	char	chr_flg;
	int		i;

	i = 0;
	while (s[i])
	{
		flg = 0;
		chr_flg = 0;
		while (is_whitespace(s[i]))
			i++;
		if (!s[i])
			break ;
		if ((s[i] == '\'' || s[i] == '"'))
		{
			chr_flg = s[i];
			flg = 1;
		}
		cmd_add_back(cmds,
			cmd_new(func_helper(s, flg, chr_flg, &i)));
	}
}
