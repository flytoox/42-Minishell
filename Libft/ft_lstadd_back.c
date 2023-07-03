/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 05:43:52 by obelaizi          #+#    #+#             */
/*   Updated: 2022/11/02 21:31:03 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*check;

	if (!new)
		return ;
	if (!(*lst))
	{
		ft_lstadd_front(lst, new);
		return ;
	}
	check = *lst;
	while (check->next)
		check = check->next;
	check->next = new;
}
