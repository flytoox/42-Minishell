/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 22:22:06 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/09 15:07:29 by obelaizi         ###   ########.fr       */
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
	// char	*tmp;
	// int		i;

	// i = -1;
	// while (g_data.input[++i])
	// {
	// 	if (g_data.input[i] == '$')
	// 	{
	// 	}
	// }
}
