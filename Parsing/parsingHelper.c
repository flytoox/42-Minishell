/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingHelper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 01:14:45 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/31 01:14:51 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rmv_frst_chr(char *s, int i)
{
	int		j;

	j = i;
	while (s[++i])
		s[j++] = s[i];
	s[j] = '\0';
}

void	do_the_work(t_cmd *tmp)
{
	int	flg;
	int	i;

	flg = 0;
	i = -1;
	while (tmp->s[++i])
	{
		if (!flg && (tmp->s[i] == '"' || tmp->s[i] == '\''))
			flg = i + 1;
		else if (flg && tmp->s[i] == tmp->s[flg - 1])
		{
			rmv_frst_chr(tmp->s, i);
			rmv_frst_chr(tmp->s, flg - 1);
			flg = 0;
			i -= 2;
		}
	}
}

void	remove_quotes(t_pars *p)
{
	t_cmd	*tmp;

	while (p)
	{
		tmp = p->cmd;
		while (tmp)
		{
			do_the_work(tmp);
			tmp = tmp->next;
		}
		p = p->next;
	}
}

void	token_it(t_cmd *node)
{
	node->quote = F;
	if (!ft_strncmp(node->s, "|", 1))
		node->type = PIPE;
	else if (!ft_strncmp(node->s, "<<", 2))
		node->type = HEREDOC;
	else if (!ft_strncmp(node->s, ">>", 2))
		node->type = APPEND;
	else if (!ft_strncmp(node->s, ">", 1))
		node->type = OUT;
	else if (!ft_strncmp(node->s, "<", 1))
		node->type = IN;
	else if (node->prev && (node->prev->type == OUT
			|| node->prev->type == IN || node->prev->type == APPEND))
		node->type = FD;
	else if (node->prev && node->prev->type == HEREDOC)
	{
		node->type = DELIM;
		if (count_str(node->s, "\"") || count_str(node->s, "'"))
			node->quote = T;
	}
	else
		node->type = CMD;
}

void	tokens(void)
{
	t_cmd	*tmp;

	token_it(g_data.cmds);
	tmp = g_data.cmds;
	while (tmp)
	{
		token_it(tmp);
		tmp = tmp->next;
	}
}
