/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:42:18 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/11 01:46:32 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(char *str)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < (int)ft_strlen(str))
		if (str[i] != '\'' && str[i] != '"')
			str[++j] = str[i];
	str[++j] = '\0';
}

void	tokens(char *str)
{
	char	**splt;
	int		i;
	t_cmd	*tmp;

	cust_split(str);
	tmp = g_data.cmds;
	while (tmp)
	{
		printf("%s      ", tmp->s);
		tmp = tmp->next;
	}
	printf("\n--------------------\n");
	upgrade_splt("|");
	upgrade_splt("<<");
	upgrade_splt(">>");
	upgrade_splt(">");
	upgrade_splt("<");
	tmp = g_data.cmds;
	while (tmp)
	{
		if (!ft_strncmp(tmp->s, "|", 1))
			printf("\033[1;32m|      \033[0m");
		else
			printf("%s      ", tmp->s);
		tmp = tmp->next;
	}
	printf("\n--------------------\n");
}

void	parse(char *str)
{
	if (is_closed(str))
	{
		printf("Dude close ur things\n");
		return ;
	}
	// if (is_syntax_error(str))
	// {
	// 	printf("Syntax error\n");
	// 	return ;
	// }
	if (!*str)
		return ;
	tokens(str);
}
