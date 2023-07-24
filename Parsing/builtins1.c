/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:31:14 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/23 00:30:20 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env(int is_env)
{
	t_env	*node;

	node = g_data.env;
	if (is_env)
	{
		while (node)
		{
			if (node->value)
				printf("%s=%s\n", node->key, node->value);
			node = node->next;
		}
		return ;
	}
	while (node)
	{
		if (node->value)
			printf("declare -x %s=\"%s\"\n", node->key, node->value);
		else
			printf("declare -x %s\n", node->key);
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
			env_delone(node);
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
	char	*vl_vr;
	int		i;

	node = g_data.env;
	if (check_parse_export(argument))
	{
		printf("minishell: export: `%s': not a valid identifier\n", argument);
		return ;
	}
	nm_vr = get_name_var(argument);
	i = -1;
	vl_vr = get_val_var(argument);
	while (node)
	{
		if (nm_vr[ft_strlen(nm_vr) - 1] == '+')
		{
			if (!ft_strncmp(node->key, nm_vr, ft_strlen(nm_vr) - 1))
			{
				if (vl_vr)
					node->value = ft_strjoin(node->value, vl_vr);
				free(nm_vr);
				return ;
			}
		}
		if (!ft_strncmp(node->key, nm_vr, ft_strlen(nm_vr)))
		{
			if (vl_vr)
				node->value = vl_vr;
			free(nm_vr);
			return ;
		}
		node = node->next;
	}
	env_add_back(&g_data.env, env_new(nm_vr, vl_vr));
}
