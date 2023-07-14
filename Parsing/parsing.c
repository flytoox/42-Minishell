/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:42:18 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/13 22:10:05 by obelaizi         ###   ########.fr       */
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
void	remove_quotes(void)
{
	// int		flg;
	// int		i;
	// int		j;
	// t_cmd	*tmp;

	// tmp = g_data.cmds;
	// while (tmp)
	// {
	// 	i = -1;
	// 	j = -1;
	// 	flg = 0;
	// 	if (tmp->s[0] != '\'' && tmp->s[0] != '"')
	// 	{
	// 		tmp = tmp->next;
	// 		continue ;
	// 	}
	// 	while (tmp->s[++i])
	// 	{
	// 		// if ((tmp->s[i] == '\'' || tmp->s[i] == '"') && !flg)
	// 		// 	flg = i + 1;
	// 		// else if (flg && tmp->s[i] == tmp->s[flg - 1])
	// 		// 	flg = 0;
	// 		// else if ()
	// 	}
	// 	tmp = tmp->next;
	// }
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
	expand();
	// execute();
	t_cmd *tmp = g_data.cmds;
	printf("cmds:\n");
	while (tmp)
	{
		printf("------------------\n");
		printf("s: {%s}\n", tmp->s);
		printf("TYPE: {%u}\n", tmp->type);
		printf("------------------\n");
		tmp = tmp->next;
	}
	printf("end\n");
	if (is_syntax_error())
	{
		printf("Minishell: syntax error near unexpected token `|'\n");
		return ;
	}
	// remove_quotes();
}
