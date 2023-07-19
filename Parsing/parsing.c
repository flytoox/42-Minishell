/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:42:18 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/16 02:04:08 by aait-mal         ###   ########.fr       */
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
void	remove_char(char *s, char q)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (s[++i])
	{
		if (s[i] == q)
			continue ;
		s[++j] = s[i];
	}
	s[++j] = '\0';
}

void	tokens_quotes(t_cmd *tmp)
{
	int		flg;
	int		i;

	flg = 1;
	i = 0;
	while (tmp->s[++i])
	{
		if (!flg || (tmp->s[i] == tmp->s[flg - 1] && !tmp->s[i + 1]))
			break ;
		else if (tmp->s[i] == tmp->s[flg - 1]
			&& tmp->s[i + 1] != tmp->s[flg - 1])
			flg = 0;
		else if (tmp->s[i] == tmp->s[flg - 1]
			&& tmp->s[i + 1] == tmp->s[flg - 1])
			i++;
	}
	if (flg)
	{
		if (tmp->s[0] == '\'')
			tmp->quote = SQ;
		else if (tmp->s[0] == '"')
			tmp->quote = DQ;
		remove_char(tmp->s, tmp->s[0]);
	}
}

void	token_it(t_cmd *node)
{
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
	else
		node->type = CMD;
	if (node->s[0] == '\'' || node->s[0] == '"')
		tokens_quotes(node);
	if (node->quote != SQ && node->quote != DQ)
		node->quote = 0;
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
	parse_front(&g_data.pars, parse_new(g_data.cmds));// ls -al | wc -al
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
	upgrade_splt("|");
	upgrade_splt("<<");
	upgrade_splt(">>");
	upgrade_splt(">");
	upgrade_splt("<");
	make_it_prev();
	tokens();
	if (is_syntax_error())
	{
		printf("Minishell: syntax error near unexpected token `|'\n");
		return ;
	}
	make_new_lst();
	printf("------------------------------------------------\n");
	t_pars	*tmp = g_data.pars;
	while (tmp)
	{
		t_cmd *tmp1 = tmp->cmd;
		expand(tmp1);
		while (tmp1)
		{
			printf("| {%s} | TYPE: {%u} | quote: {%u}|\t", tmp1->s, tmp1->type, tmp1->quote);
			tmp1 = tmp1->next;
		}
		printf("\n------------------\n");
		tmp = tmp->next;
	}
	open_files();
	// env(1);
	// printf("-------------------------------------------------\n");
	// env(1);
	// printf("------------------------------------------------\n");
	// env(0);
	// execute();
}

void	open_files(void)
{
	int		fd;
	t_pars	*tmp;
	t_cmd	*cmd;

	tmp = g_data.pars;
	while (tmp)
	{
		cmd = tmp->cmd;
		while (cmd)
		{
			if (cmd->type == IN)
			{
				fd = open(cmd->next->s, O_RDONLY);
				if (fd == -1)
				{
					printf("Minishell: %s: No such file or directory\n", cmd->next->s);
					break ;
				}
				close(fd);
			}
			else if (cmd->type == OUT)
			{
				fd = open(cmd->next->s, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				close(fd);
			}
			else if (cmd->type == APPEND)
			{
				fd = open(cmd->next->s, O_WRONLY | O_CREAT | O_APPEND, 0644);
				close(fd);
			}
			cmd = cmd->next;
		}
		tmp = tmp->next;
	}
}