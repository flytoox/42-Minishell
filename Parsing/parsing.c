/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:42:18 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/13 01:51:37 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_quotes(void)
{
	// int		flg;
	// int		i;
	// t_cmd	*tmp;
	
	// tmp = g_data.cmds;
	// while (tmp)
	// {
		
	// 	tmp = tmp->next;
	// }
	// i = -1;
	// flg = 0;
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
	execute();
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
}
