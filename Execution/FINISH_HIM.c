/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FINISH_HIM.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:20:46 by obelaizi          #+#    #+#             */
/*   Updated: 2023/08/06 18:12:18 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_valid(char *str)
{
	int		i;

	if (!str)
		return (true);
	if (ft_strlen(str) > 19)
		return (false);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (ft_strlen(str) == 19)
		if (ft_strcmp(str, "9223372036854775807") > 0)
			return (false);
	if (!str[i])
		return (true);
	return (false);
}
