/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 22:22:06 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/31 02:07:49 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_expand(t_cmd *cmd)
{
	while (cmd)
	{
		cmd->type = CMD;
		cmd = cmd->next;
	}
}

void	expand_it(t_cmd *node, int *i, int *before_equal, int *expanded)
{
	char	*val;
	char	*rest;
	char	*tmp;

	if (i && node->s[*i - 1] == '=')
		*before_equal = 1;
	else
		*before_equal = 0;
	*expanded = 1;
	(*i)++;
	rest = ft_substr(node->s, *i, ft_strlen(node->s));
	trim_it(rest);
	val = env_value(&node->s[*i], g_data.env);
	node->s[*i - 1] = '\0';
	tmp = node->s;
	if (val)
		node->s = ft_strjoin(node->s, val);
	tmp = node->s;
	node->s = ft_strjoin(node->s, rest);
	(*i)--;
}

void	link_the_expanded(t_cmd *node, t_pars **pars)
{
	t_cmd	*tmp_next;
	t_cmd	*tmp_node;

	tmp_next = node->next;
	tmp_node = NULL;
	cust_split(node->s, &tmp_node);
	token_expand(tmp_node);
	cmd_add_back(&tmp_node, tmp_next);
	if (!node->prev)
		(*pars)->cmd = tmp_node;
	else
		node->prev->next = tmp_node;
}

void	is_it_expanded(t_cmd *node, t_pars **pars)
{
	int		expanded;
	int		i;
	int		flg;
	int		before_equal;

	expanded = 0;
	flg = 0;
	i = -1;
	while (node->s[++i] && node->type != DELIM)
	{
		if ((node->s[i] == '\'' || node->s[i] == '"') && !flg)
			flg = i + 1;
		else if (flg && node->s[i] == node->s[flg - 1])
			flg = 0;
		else if (node->s[i] == '$' && node->s[i + 1]
			&& (!flg || (flg && node->s[flg - 1] == '"')))
			expand_it(node, &i, &before_equal, &expanded);
	}
	if ((!is_export((*pars)->cmd)
			|| (is_export((*pars)->cmd) && !before_equal)) && expanded)
		link_the_expanded(node, pars);
}

void	expand(t_pars *pars)
{
	t_cmd	*node;
	t_pars	*tmp;

	tmp = pars;
	while (pars)
	{
		pars->in = FD_INIT;
		pars->out = FD_INIT;
		node = pars->cmd;
		while (node)
		{
			is_it_expanded(node, &pars);
			node = node->next;
		}
		pars = pars->next;
	}
}
