/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 01:47:36 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/15 00:13:26 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_builtins(void)
{
	g_data.builtins = malloc(sizeof(char *) * 8);
	g_data.builtins[0] = "echo";
	g_data.builtins[1] = "cd";
	g_data.builtins[2] = "pwd";
	g_data.builtins[3] = "export";
	g_data.builtins[4] = "unset";
	g_data.builtins[5] = "env";
	g_data.builtins[6] = "exit";
	g_data.builtins[7] = NULL;
}

t_pars	*set_parsed(t_cmd *cmd)
{
	t_pars	*parsed;
	t_cmd	*tmp;
	t_cmd	*tmp2;

	parsed = g_data.pars;
	parsed = malloc(sizeof(t_pars));
	parsed->cmd = cmd;
	tmp2 = parsed->cmd;
	while (parsed->cmd)
	{
		if (parsed->cmd->type == PIPE)
		{
			tmp = parsed->cmd->next;
			parsed->cmd->prev->next = NULL;
			break ;
		}
		parsed->cmd = parsed->cmd->next;
	}
	parsed->cmd = tmp2;
	parsed->next = NULL;
	return (parsed);
}

int	check_builtins(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (g_data.builtins[i])
	{
		if (!ft_strncmp(g_data.builtins[i], cmd->s, ft_strlen(cmd->s)))
		{
			if (i == 0)
				printf("echo\n");
			else if (i == 1)
				printf("cd\n");
			else if (i == 2)
				printf("pwd\n");
			else if (i == 3)
				printf("export\n");
			else if (i == 4)
				printf("unset\n");
			else if (i == 5)
				printf("env\n");
			else if (i == 6)
				printf("exit\n");
			return (1);
		}
		i++;
	}
	printf("not a builtin\n");
	return (0);
}

void	execute(void)
{
	t_pars	*parsed;
	t_cmd	*cmd;

	printf("\n\n========Execute\n");
	cmd = g_data.cmds;
	parsed = set_parsed(cmd);
	while (parsed)
	{
		while (parsed->cmd)
		{
			printf("parsed->cmd->s = %s\n", parsed->cmd->s);
			parsed->cmd = parsed->cmd->next;
		}
		if (!check_builtins(cmd))
		{
			if (fork() == 0)
			{
				char *arr[] = {path_cmd(cmd->s), NULL};
				execve(path_cmd(cmd->s), arr, NULL);
				printf("%s", path_cmd(cmd->s));
			}
			else
				wait(NULL);
		}
		parsed = parsed->next;
	}
}
