/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandHelper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 01:13:27 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/31 01:14:02 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*env_value(char *key, t_env *node)
{
	char	*tmp;
	int		i;

	if (!ft_strncmp(key, "?", 1) && !(ft_isalnum(key[1]) || key[1] == '_'))
		return (ft_itoa(g_data.exit_status));
	tmp = malloc(ft_strlen(key) + 1);
	if (!tmp)
		exit (1);
	garbg_add_back(&g_data.garbage, garbg_new(tmp));
	i = 0;
	while (key[i] && (ft_isalnum(key[i]) || key[i] == '_'))
	{
		tmp[i] = key[i];
		i++;
	}
	tmp[i] = '\0';
	if (!ft_strcmp(tmp, "?"))
		return (ft_itoa(g_data.exit_status));
	while (node)
	{
		if (!ft_strcmp(node->key, tmp))
			return (node->value);
		node = node->next;
	}
	return (NULL);
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

bool	is_export(t_cmd *cmd)
{
	t_cmd	*node;

	node = cmd;
	while (node)
	{
		if (node->type == CMD)
		{
			if (!ft_strcmp(node->s, "export"))
				return (true);
			else
				return (false);
		}
		node = node->next;
	}
	return (false);
}
