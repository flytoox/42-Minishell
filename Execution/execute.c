/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 01:47:36 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/14 21:37:15 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(void)
{
	t_cmd		*cmds;

	cmds = g_data.cmds;
	printf("CMD SIZE: %d\n", cmd_size(cmds));
	while (cmds)
	{
		// printf("CMD: %s\n", cmds->cmd);
		cmds = cmds->next;
	}
	printf("\n\n\n");
}
