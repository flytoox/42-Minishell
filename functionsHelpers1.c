/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functionsHelpers1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:43:34 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/11 01:23:03 by obelaizi         ###   ########.fr       */
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

static void	upgrade_splt_helper1(t_cmd **node, int i, const char *sep)
{
	t_cmd	*tmp;

	tmp = (*node)->next;
	cmd_front(&tmp, cmd_new(ft_substr((*node)->s, i + ft_strlen(sep),
				ft_strlen((*node)->s) - i - ft_strlen(sep))));
	cmd_front(&tmp, cmd_new(ft_strdup(sep)));
	(*node)->next = tmp;
	(*node)->s[i] = '\0';
	(*node) = (*node)->next;
}

int	upgrade_splt_helper(t_cmd **node, char *s)
{
	if (!ft_strncmp(s, "<<", ft_strlen(s))
		|| !ft_strncmp(s, ">>", ft_strlen(s)))
	{
		(*node) = (*node)->next;
		return (1);
	}
	return (0);
}

void	upgrade_splt(const char *sep)
{
	t_cmd	*node;
	int		i;
	int		flg;

	node = g_data.cmds;
	while (node)
	{
		if (upgrade_splt_helper(&node, node->s))
			continue ;
		i = -1;
		flg = 0;
		while (node->s[++i])
		{
			if ((node->s[i] == '\'' || node->s[i] == '"') && !flg)
				flg = i + 1;
			else if (flg && node->s[i] == node->s[flg - 1])
				flg = 0;
			else if (!ft_strncmp(node->s + i, sep, ft_strlen(sep)) && !flg)
			{
				upgrade_splt_helper1(&node, i, sep);
				break ;
			}
		}
		node = node->next;
	}
}
