/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:31:14 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/08 22:02:06 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(void)
{
	t_env	*node;

	node = g_data.env;
	while (node)
	{
		printf("%s=%s\n", node->key, node->value);
		node = node->next;
	}
}

void	unset(char *s)
{
	t_env	*node;
	t_env	*tmp;

	node = g_data.env;
	while (node)
	{
		if (!ft_strncmp(node->key, s, ft_strlen(s)))
		{
			tmp->next = node->next;
			env_lstdelone(node);
			return ;
		}
		tmp = node;
		node = node->next;
	}
}

void	export(char *argument)
{
	t_env	*node;
	char	*nm_vr;
	int		i;

	if (!ft_strchr(argument, '='))
		return ;
	node = g_data.env;
	nm_vr = get_name_var(argument);
	i = -1;
	while (node)
	{
		if (!ft_strncmp(node->key, nm_vr, ft_strlen(nm_vr)))
		{
			node->value = get_val_var(argument);
			free(nm_vr);
			return ;
		}
		node = node->next;
	}
	env_lstadd_back(&g_data.env, env_lstnew(nm_vr, get_val_var(argument)));
}
