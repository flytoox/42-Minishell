/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 22:22:06 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/13 01:37:54 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_value(char *key)
{
	t_env	*node;

	node = g_data.env;
	while (node)
	{
		if (!ft_strncmp(node->key, key, ft_strlen(key)))
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

void	expand(void)
{
	char	*res;
	t_cmd	*node;
	int		i;
	int		flg;

	res = ft_strdup("");
	node = g_data.cmds;
	while (node)
	{
		flg = 0;
		i = -1;
		while (node->s[++i])
		{
			if ((node->s[i] == '\'' || node->s[i] == '"') && !flg)
				flg = i + 1;
			else if (flg && node->s[i] == node->s[flg - 1])
				flg = 0;
			else if (node->s[i] == '$' && (!flg ||
					(flg && node->s[flg - 1] == '"')))
			{
				printf("TRUE\n");
			}
		}
		node = node->next;
	}
}
