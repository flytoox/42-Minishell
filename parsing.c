/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:42:18 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/09 19:12:26 by obelaizi         ###   ########.fr       */
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

	g_data.tkns.pipe = count_str(str, "|");
	g_data.tkns.heredoc = count_str(str, "<<");
	g_data.tkns.append = count_str(str, ">>");
	g_data.tkns.out = count_str(str, ">");
	g_data.tkns.in = count_str(str, "<");
	splt = cust_split(str);
	i = 0;
	while (splt[i])
	{
		printf("|%s|\n", splt[i]);
		i++;
	}
	free_dbl_pntr((void **)splt);
}

void	parse(char *str)
{
	// char	**splt;
	if (is_closed(str))
	{
		printf("Dude close ur things\n");
		return ;
	}
	if (!*str)
		return ;
	// splt = ft_split(str, '|');
	tokens(str);
}
