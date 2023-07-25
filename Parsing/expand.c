/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 22:22:06 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/25 00:47:26 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*env_value(char *key)
{
	t_env	*node;
	char	*tmp;
	int		i;

	node = g_data.env;
	if (!ft_strncmp(key, "?", 1))
		return (ft_itoa(g_data.exit_status));
	tmp = malloc(ft_strlen(key) + 1);
	i = 0;
	while (key[i] && (ft_isalnum(key[i]) || key[i] == '_'))
	{
		tmp[i] = key[i];
		i++;
	}
	tmp[i] = '\0';
	if (!ft_strcmp(tmp, "?"))
		return (free(tmp), ft_itoa(g_data.exit_status));
	while (node)
	{
		if (!ft_strcmp(node->key, tmp))
			return (free(tmp), node->value);
		node = node->next;
	}
	return (free(tmp), ft_strdup(""));
}

void	trim_it(char *s)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!ft_strncmp(s, "?", 1))
	{
		while (s[++i])
			s[i] = s[i + 1];
		return ;
	}
	while (s[++i] && (ft_isalnum(s[i]) || s[i] == '_'))
		;
	while (s[i])
		s[++j] = s[i++];
	s[++j] = '\0';
}

void	expand(t_cmd *node)
{
	char	*val;
	char	*rest;
	int		i;
	int		flg;
	char	*tmp;

	while (node)
	{
		flg = 0;
		i = -1;
		while (node->s[++i] && node->type != DELIM)
		{
			if ((node->s[i] == '\'' || node->s[i] == '"') && !flg)
				flg = i + 1;
			else if (flg && node->s[i] == node->s[flg - 1])
				flg = 0;
			else if (node->s[i] == '$' && node->s[i + 1] && (!flg || (flg && node->s[flg - 1] == '"')))
			{
				i++;
				rest = ft_substr(node->s, i, ft_strlen(node->s));
				trim_it(rest);
				val = env_value(&node->s[i]);
				node->s[i - 1] = '\0';
				tmp = node->s;
				node->s = ft_strjoin(node->s, val);
				tmp = node->s;
				node->s = ft_strjoin(node->s, rest);
			}
		}
		remove_quotes(node->s);
		node = node->next;
	}
}
