/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:31:14 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/30 03:38:12 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env(int is_env)
{
	t_env	*node;

	export("_=/usr/bin/env");
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
		if (ft_strcmp(node->key, "_"))
		{
			if (node->value)
				printf("declare -x %s=\"%s\"\n", node->key, node->value);
			else
				printf("declare -x %s\n", node->key);
		}
		node = node->next;
	}
}

void	unset(char *s)
{
	t_env	*node;
	t_env	*tmp;

	if (g_data.env && !ft_strcmp(g_data.env->key, s))
	{
		node = g_data.env;
		g_data.env = g_data.env->next;
		return (env_delone(node));
	}
	node = g_data.env;
	while (node)
	{
		if (!ft_strcmp(node->key, s))
		{
			tmp->next = node->next;
			return (env_delone(node));
		}
		tmp = node;
		node = node->next;
	}
}

int export_helper(char *nm_vr, char *vl_vr, t_env *node)
{
	if (nm_vr[ft_strlen(nm_vr) - 1] == '+')
	{
		if (!ft_strncmp(node->key, nm_vr, ft_strlen(nm_vr) - 1))
		{
			if (vl_vr)
				node->value = ft_strjoin(node->value, vl_vr);
			return (1);
		}
	}
	if (!ft_strcmp(node->key, nm_vr))
	{
		if (vl_vr)
			node->value = vl_vr;
		return (1);
	}
	return (0);
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
		if (export_helper(nm_vr, vl_vr, node))
			return ;
		node = node->next;
	}
	if (nm_vr[ft_strlen(nm_vr) - 1] == '+')
		nm_vr[ft_strlen(nm_vr) - 1] = '\0';
	env_add_back(&g_data.env, env_new(nm_vr, vl_vr));
}
