/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:42:18 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/28 23:16:36 by aait-mal         ###   ########.fr       */
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


int	parse(char *str)
{
	if (!*str)
		return ;
	if (is_closed(str))
		return (printf("Dude close ur things\n"));
	g_data.cmds = NULL;
	cust_split(str, &g_data.cmds);
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
		return (printf("Minishell: syntax error near unexpected token `|'\n"));
	make_new_lst();
	expand(g_data.pars);
	open_files(g_data.pars);
	make_pars_prev();
	execute(g_data.pars);
}

void	out_append(t_pars *tmp, t_cmd *cmd)
{
	if (tmp->out)
		close(tmp->out);
	if (cmd->prev->type == OUT)
		tmp->out = open(cmd->s, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cmd->prev->type == APPEND)
		tmp->out = open(cmd->s, O_WRONLY | O_CREAT | O_APPEND, 0644);
}

void	in(t_pars *tmp, t_cmd *cmd)
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

void	open_files(t_pars *tmp)
{
	t_cmd	*cmd;

	while (tmp)
	{
		tmp->in = FD_INIT;
		tmp->out = FD_INIT;
		cmd = tmp->cmd->next;
		while (cmd)
		{
			if (cmd->prev->type == OUT || cmd->prev->type == APPEND)
				out_append(tmp, cmd);
			else if (cmd->prev->type == IN)
				in(tmp, cmd);
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
