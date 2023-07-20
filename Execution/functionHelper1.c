/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functionHelper1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 23:11:34 by aait-mal          #+#    #+#             */
/*   Updated: 2023/07/20 23:03:17 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_cmd(char *cmd, char *msg)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = 0;
	if (!cmd[0])
		return (printf("Minishell: %s%s", cmd, msg), exit(1), NULL);
	if (!access(cmd, F_OK))
		return (cmd);
	tmp2 = cmd;
	cmd = ft_strjoin("/", tmp2);
	while (g_data.path[i])
	{
		if (tmp)
			free(tmp);
		tmp = ft_strjoin(g_data.path[i], cmd);
		if (!access(tmp, F_OK))
			return (free(cmd), cmd = tmp, cmd);
		i++;
	}
	return (printf("Minishell: %s%s", tmp2, msg), exit(1), NULL);
}
