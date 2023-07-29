/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 22:22:06 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/28 23:17:02 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*env_value(char *key)
{
	t_env	*node;
	char	*tmp;
	int		i;

	node = g_data.env;
	if (!ft_strcmp(key, "?"))
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
	return (free(tmp), NULL);
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

void	token_expand(t_cmd *cmd)
{

}

void	expand(t_pars *pars)
{
	char	*val;
	char	*rest;
	int		i;
	int		flg;
	char	*tmp;
	t_cmd	*tmp_node;
	t_cmd	*node;

	while (pars)
	{
		node = pars->cmd;
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
					if (val)
						node->s = ft_strjoin(node->s, val);
					tmp = node->s;
					node->s = ft_strjoin(node->s, rest);
				}
			}
			// if (!is_export(pars->cmd))
			// {
			// 	tmp_node = node->next;
			// 	node->next = NULL;
			// 	cust_split(node->s, &node);
			// 	cmd_add_back(&pars->cmd, tmp_node);
			// 	t_cmd *tmp_node2 = pars->cmd;
			// 	while (tmp_node2)
			// 	{
			// 		printf("s = %s\n", tmp_node2->s);
			// 		tmp_node2 = tmp_node2->next;
			// 	}
			// }
			remove_quotes(node->s);
			node = node->next;
		}
		pars = pars->next;
	}
}
