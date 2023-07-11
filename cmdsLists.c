/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdsLists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:51:07 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/10 23:26:05 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmd_new(char *s)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (0);
	node->s = s;
	node->next = 0;
	return (node);
}

void	cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*check;

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

int	cmd_size(t_cmd *lst)
{
	t_cmd	*i;
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

void	cmd_clear(t_cmd **lst)
{
	int		size;
	t_cmd	*tmp;

	if (!(*lst))
		return ;
	size = cmd_size(*lst);
	while (size--)
	{
		tmp = (*lst)->next;
		free((*lst)->s);
		free(*lst);
		*lst = tmp;
	}
}

void	cmd_front(t_cmd **lst, t_cmd *new)
{
	if (!new)
		return ;
	new ->next = *lst;
	*lst = new;
}
