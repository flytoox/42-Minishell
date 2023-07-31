/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:42:18 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/31 02:09:42 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_new_lst(void)
{
	t_cmd	*tmp;
	t_cmd	*head;

	tmp = g_data.cmds;
	g_data.pars = NULL;
	parse_front(&g_data.pars, parse_new(g_data.cmds));
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			head = tmp->next;
			head->prev = NULL;
			tmp->prev->next = NULL;
			tmp = head;
			parse_add_back(&g_data.pars, parse_new(head));
		}
		else
			tmp = tmp->next;
	}
}

int	parse(char *str)
{
	if (!*str)
		return (0);
	if (is_closed(str))
		return (printf("Dude close ur things\n"));
	g_data.cmds = NULL;
	cust_split(str, &g_data.cmds);
	if (!g_data.cmds)
		return (0);
	upgrade_splt("|");
	upgrade_splt("<<");
	upgrade_splt(">>");
	upgrade_splt(">");
	upgrade_splt("<");
	make_cmd_prev();
	tokens();
	if (is_syntax_error())
		return (printf("Minishell: syntax error near unexpected token\n"));
	make_new_lst();
	expand(g_data.pars);
	remove_quotes(g_data.pars);
	open_files(g_data.pars);
	make_pars_prev();
	execute(g_data.pars);
	return (0);
}

void	out_append(t_pars *tmp, t_cmd *cmd)
{
	if (tmp->out)
		close(tmp->out);
	if (cmd->type == OUT)
		tmp->out = open(cmd->next->s, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cmd->type == APPEND)
		tmp->out = open(cmd->next->s, O_WRONLY | O_CREAT | O_APPEND, 0644);
}

int	in(t_pars *tmp, t_cmd *cmd)
{
	if (tmp->in)
		close(tmp->in);
	tmp->in = open(cmd->next->s, O_RDONLY);
	if (tmp->in == -1)
	{
		printf("Minishell: %s: No such file or directory\n",
			cmd->next->s);
		tmp->in = FILE_NOT_FOUND;
		return (1);
	}
	return (0);
}

void	open_files(t_pars *tmp)
{
	t_cmd	*cmd;

	while (tmp)
	{
		cmd = tmp->cmd;
		while (cmd && cmd->next)
		{
			if (cmd->type == OUT || cmd->type == APPEND)
				out_append(tmp, cmd);
			else if (cmd->type == IN)
			{
				if (in(tmp, cmd))
					break ;
			}
			else if (cmd->type == HEREDOC)
			{
				if (tmp->in)
					close(tmp->in);
				tmp->in = -200;
			}
			cmd = cmd->next;
		}
		tmp = tmp->next;
	}
}
