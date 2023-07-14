/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functionHelper1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 23:11:34 by aait-mal          #+#    #+#             */
/*   Updated: 2023/07/15 00:52:46 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_cmd(char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = 0;
	if (!access(cmd, F_OK))
		return (cmd);
	cmd = ft_strjoin("/", cmd);
	while (g_data.path[i])
	{
		if (tmp)
			free(tmp);
		tmp = ft_strjoin(g_data.path[i], cmd);
		if (!access(tmp, F_OK))
			return (free(cmd), cmd = tmp, cmd);
		i++;
	}
	return (printf("pipex: command not found\n"), exit(1), 0);
}
