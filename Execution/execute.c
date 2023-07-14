/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 01:47:36 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/15 00:49:38 by aait-mal         ###   ########.fr       */
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

char	**get_cmds_args(t_cmd *cmd)
{
	char	**args;
	int		i;

	i = 0;
	args = malloc(sizeof(char *) * (cmd_size(cmd) + 1));
	while (cmd)
	{
		args[i] = cmd->s;
		cmd = cmd->next;
		i++;
	}
	args[i] = NULL;
	return (args);
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
	char	**args;

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
				args = get_cmds_args(cmd);
				args[0] = path_cmd(cmd->s);
				execve(path_cmd(cmd->s), args, NULL);
				printf("%s", path_cmd(cmd->s));
			}
			else
				wait(NULL);
		}
		parsed = parsed->next;
	}
}
