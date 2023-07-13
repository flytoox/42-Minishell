/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 01:47:36 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/13 01:53:41 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(void)
{
	t_cmd	*cmd;

	cmd = g_data.cmds;
	printf("CMD SIZE: %d\n", cmd_size(cmd));
	while (cmd)
	{
		if (cmd->s)
			printf("%s ", cmd->s);
		cmd = cmd->next;
	}
	printf("\n\n\n");
}