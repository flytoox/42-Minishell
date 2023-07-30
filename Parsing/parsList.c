/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsList.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 22:58:33 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/30 03:32:33 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pars	*parse_new(t_cmd *cmd)
{
	t_pars	*node;

	node = malloc(sizeof(t_pars));
	if (!node)
		return (0);
	garbg_add_back(&g_data.garbage, garbg_new(node));
	node->cmd = cmd;
	node->next = 0;
	return (node);
}

void	parse_add_back(t_pars **lst, t_pars *new)
{
	t_pars	*check;

	if (!new)
		return ;
	if (!(*lst))
	{
		new->next = *lst;
		*lst = new;
		return ;
	}
	check = *lst;
	while (check->next)
		check = check->next;
	check->next = new;
}

int	parse_size(t_pars *lst)
{
	t_pars	*i;
	int		count;

	if (!lst)
		return (0);
	count = 0;
	i = lst;
	while (i)
	{
		count++;
		i = i->next;
	}
	return (count);
}

void	parse_clear(t_pars **lst)
{
	int		size;
	t_pars	*tmp;

	if (!(*lst))
		return ;
	size = parse_size(*lst);
	while (size--)
	{
		tmp = (*lst)->next;
		cmd_clear(&(*lst)->cmd);
		free(*lst);
		*lst = tmp;
	}
}

void	parse_front(t_pars **lst, t_pars *new)
{
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}
