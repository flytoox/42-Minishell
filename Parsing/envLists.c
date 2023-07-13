/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envLists.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 21:15:36 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/13 01:41:45 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*env_new(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (0);
	node->key = key;
	node->value = value;
	node->next = 0;
	return (node);
}

void	env_add_back(t_env **lst, t_env *new)
{
	t_env	*check;

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

void	env_delone(t_env *lst)
{
	if (!lst)
		return ;
	free(lst->key);
	free(lst->value);
	free(lst);
}

int	env_size(t_env *lst)
{
	t_env	*i;
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

void	env_clear(t_env **lst)
{
	int		size;
	t_env	*tmp;

	if (!(*lst))
		return ;
	size = env_size(*lst);
	while (size--)
	{
		tmp = (*lst)->next;
		env_delone(*lst);
		*lst = tmp;
	}
}
