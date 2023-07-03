/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 05:52:14 by obelaizi          #+#    #+#             */
/*   Updated: 2022/11/02 18:32:05 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*begin;

	if (!lst || !f || !del)
		return (0);
	begin = 0;
	while (lst)
	{
		node = ft_lstnew(f(lst->content));
		if (!node)
			ft_lstclear(&begin, del);
		ft_lstadd_back(&begin, node);
		lst = lst->next;
	}
	return (begin);
}
