/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:42:18 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/23 23:23:29 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_free(char *s1, char *s2, int flg)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (flg == 1 || flg == 3)
		free(s1);
	if (flg == 2 || flg == 3)
		free(s2);
	return (res);
}
void	rmv_frst_chr(char *s, int i)
{
	int		j;

	j = i;
	while (s[++i])
		s[j++] = s[i];
	s[j] = '\0';
}

void	remove_quotes(char *s)
{
	int		flg;
	int		i;

	flg = 0;
	i = -1;
	while (s[++i])
	{
		if (!flg && (s[i] == '"' || s[i] == '\''))
			flg = i + 1;
		else if (flg && s[i] == s[flg - 1])
		{
			rmv_frst_chr(s, i);
			rmv_frst_chr(s, flg - 1);
			flg = 0;
			i -= 2;
		}
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
	char	**splt;
	int		i;
	t_cmd	*tmp;

	token_it(g_data.cmds);
	tmp = g_data.cmds;
	while (tmp)
	{
		token_it(tmp);
		tmp = tmp->next;
	}
}

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
			free(tmp->s);
			free (tmp);
			tmp = head;
			parse_add_back(&g_data.pars, parse_new(head));
		}
		else
			tmp = tmp->next;
	}
}

void	expand_remove_quotes(void)
{
	t_cmd	*tmp;

	tmp = g_data.cmds;
	while (tmp)
	{
		expand(tmp);
		tmp = tmp->next;
	}
}

void	parse(char *str)
{
	if (!*str)
		return ;
	if (is_closed(str))
	{
		printf("Dude close ur things\n");
		return ;
	}
	cust_split(str);
	if (!g_data.cmds)
		return ;
	upgrade_splt("|");
	upgrade_splt("<<");
	upgrade_splt(">>");
	upgrade_splt(">");
	upgrade_splt("<");
	make_cmd_prev();
	tokens();
	if (is_syntax_error())
	{
		printf("Minishell: syntax error near unexpected token `|'\n");
		return ;
	}
	make_new_lst();

	// printf("------------------------------------------------\n");
	t_pars	*tmp = g_data.pars;
	while (tmp)
	{
		expand(tmp->cmd);
		tmp = tmp->next;
	}
	open_files();
	make_pars_prev();
	execute();
}

void	open_files(void)
{
	t_pars	*tmp;
	t_cmd	*cmd;

	tmp = g_data.pars;
	g_data.not_found = 0;
	while (tmp)
	{
		tmp->in = FD_INIT;
		tmp->out = FD_INIT;
		cmd = tmp->cmd->next;
		while (cmd)
		{
			if (cmd->prev->type == OUT
				|| cmd->prev->type == APPEND)
			{
				if (tmp->out)
					close(tmp->out);
				if (cmd->prev->type == OUT)
					tmp->out = open(cmd->s,
							O_WRONLY | O_CREAT | O_TRUNC, 0644);
				else if (cmd->prev->type == APPEND)
					tmp->out = open(cmd->s,
							O_WRONLY | O_CREAT | O_APPEND, 0644);
			}
			else if (cmd->prev->type == IN)
			{
				if (tmp->in)
					close(tmp->in);
				tmp->in = open(cmd->s, O_RDONLY);
				if (tmp->in == -1)
				{
					printf("Minishell: %s: No such file or directory\n",
						cmd->s);
					tmp->in = FILE_NOT_FOUND;
					break ;
				}
			}
			else if (cmd->prev->type == HEREDOC)
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
