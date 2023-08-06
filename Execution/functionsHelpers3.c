/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functionsHelpers3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 01:08:19 by obelaizi          #+#    #+#             */
/*   Updated: 2023/08/06 18:57:08 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	calc_cmd_size(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd)
	{
		if (cmd->type == CMD)
			i++;
		cmd = cmd->next;
	}
	return (i);
}

char	**get_cmds_args(t_cmd *cmd, t_pars *parsed)
{
	char	**args;
	int		i;

	(void)parsed;
	i = 0;
	if (!calc_cmd_size(cmd))
		return (NULL);
	args = malloc(sizeof(char *) * (calc_cmd_size(cmd) + 1));
	if (!args)
		exit(1);
	garbg_add_back(&g_data.garbage, garbg_new(args));
	while (cmd)
	{
		if (cmd->type == CMD)
			args[i++] = cmd->s;
		cmd = cmd->next;
	}
	args[i] = NULL;
	return (args);
}

void	set_builtins(void)
{
	g_data.builtins = malloc(sizeof(char *) * 8);
	if (!g_data.builtins)
		exit(1);
	garbg_add_back(&g_data.garbage, garbg_new(g_data.builtins));
	g_data.builtins[0] = "echo";
	g_data.builtins[1] = "pwd";
	g_data.builtins[2] = "env";
	g_data.builtins[3] = "exit";
	g_data.builtins[4] = "unset";
	g_data.builtins[5] = "cd";
	g_data.builtins[6] = "export";
	g_data.builtins[7] = NULL;
}

void	lunch_herdoc(t_pars *parsed)
{
	t_cmd	*cmd;
	int		in;

	while (parsed)
	{
		cmd = parsed->cmd;
		while (cmd)
		{
			if (cmd->type == DELIM)
				in = here_doc(cmd->s, cmd->quote);
			cmd = cmd->next;
		}
		if (parsed->in == -200)
			parsed->in = in;
		parsed = parsed->next;
	}
}

int	give_me_index(char **args)
{
	int		i;

	i = 0;
	while (g_data.builtins[i] && ft_strcmp(g_data.builtins[i], args[0]))
		i++;
	return (i);
}
