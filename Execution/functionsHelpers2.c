/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functionsHelpers2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 01:04:28 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/31 18:56:54 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_val_var(char *argument)
{
	char	*vl_vr;

	if (!ft_strchr(argument, '='))
		return (NULL);
	vl_vr = ft_strchr(argument, '=') + 1;
	return (ft_strdup(vl_vr));
}

char	*get_name_var(char *argument)
{
	char	*nm_vr;
	char	*vl_vr;
	int		i;

	if (!ft_strchr(argument, '='))
		return (ft_strdup(argument));
	vl_vr = ft_strchr(argument, '=') + 1;
	i = -1;
	nm_vr = malloc(ft_strlen(argument) - ft_strlen(vl_vr));
	if (!nm_vr)
		exit(1);
	garbg_add_back(&g_data.garbage, garbg_new(nm_vr));
	while (argument[++i])
	{
		if (argument[i] == '=')
		{
			nm_vr[i] = '\0';
			break ;
		}
		nm_vr[i] = argument[i];
	}
	return (nm_vr);
}

void	make_the_env(void)
{
	char	**env;
	t_env	*node;
	int		i;

	i = 0;
	node = g_data.env;
	env = malloc(sizeof(char *) * (env_size(node) + 1));
	if (!env)
		exit(1);
	garbg_add_back(&g_data.garbage, garbg_new(env));
	while (node)
	{
		if (node->value && node->key)
		{
			env[i] = ft_strjoin(node->key, "=");
			env[i] = ft_strjoin(env[i], node->value);
			i++;
		}
		node = node->next;
	}
	env[i] = NULL;
	g_data.env_tab = env;
}

void	make_the_path(void)
{
	t_env	*node;

	node = g_data.env;
	while (node)
	{
		if (!ft_strcmp(node->key, "PATH"))
		{
			g_data.path = ft_split(node->value, ':');
			return ;
		}
		node = node->next;
	}
	g_data.path = NULL;
}

void	signals_handling(int status)
{
	while (waitpid(-1, &status, 0) != -1)
		if (WIFEXITED(status))
			g_data.exit_status = WEXITSTATUS(status);
	if (WTERMSIG(status) == SIGINT)
	{
		if (!g_data.pars->next)
			g_data.exit_status = 130;
		write(1, "\n", 1);
	}
	if (WTERMSIG(status) == SIGQUIT)
	{
		if (g_data.pars->next)
			write(1, "", 1);
		else
		{
			g_data.exit_status = 131;
			write(1, "Quit: 3\n", 8);
		}
	}
	signal(SIGINT, sigusr_handler);
	signal(SIGQUIT, sigusr_handler);
}
