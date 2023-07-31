/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GarbageList.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:51:07 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/31 00:34:47 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_grbg	*garbg_new(void *s)
{
	t_grbg	*node;

	node = malloc(sizeof(t_grbg));
	if (!node)
		exit (1);
	node->ptr = s;
	node->next = 0;
	return (node);
}

void	garbg_add_back(t_grbg **lst, t_grbg *new)
{
	t_grbg	*check;

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

int	garbg_size(t_grbg *lst)
{
	t_grbg	*i;
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

void	garbg_clear(t_grbg **lst)
{
	int			size;
	t_grbg		*tmp;

	if (!(*lst))
		return ;
	size = garbg_size(*lst);
	while (size--)
	{
		tmp = (*lst)->next;
		free((*lst)->ptr);
		free(*lst);
		*lst = tmp;
	}
}

void	garbg_front(t_grbg **lst, t_grbg *new)
{
	if (!new)
		return ;
	new ->next = *lst;
	*lst = new;
}
