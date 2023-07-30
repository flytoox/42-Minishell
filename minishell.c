/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:18:45 by aait-mal          #+#    #+#             */
/*   Updated: 2023/07/30 01:20:48 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

void	sigusr_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	display_prompt(void)
{
	rl_catch_signals = 0;
	g_data.input = readline("minishell# ");
	if (!g_data.input)
	{
		// env_clear(&g_data.env);
		// free_dbl_pntr((void **)g_data.path);
		// parse_clear(&g_data.pars);
		printf("exit\n");
		exit (0);
	}
	if (g_data.input[0])
		add_history(g_data.input);
	parse(g_data.input);
	free(g_data.input);
	cmd_clear(&g_data.cmds);
}

char	*get_path(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (env[i] + 5);
	return (0);
}

void	ft_exit(void)
{
	system("leaks minishell");
}

t_env	*fill_env(char **env)
{
	int		i;
	t_env	*new_env;
	char	*name_var;
	char	*val_var;
	char	*tmp;

	new_env = NULL;
	i = -1;
	while (env[++i])
	{
		name_var = get_name_var(env[i]);
		val_var = get_val_var(env[i]);
		if (!ft_strcmp(name_var, "SHLVL"))
		{
			tmp = val_var;
			val_var = ft_itoa(ft_atoi(val_var) + 1);
			free(tmp);
		}
		env_add_back(&new_env,
			env_new(name_var, val_var));
	}
	return (new_env);
}


void	fill_the_env(void)
{
	char	*pwd;
	char	*shlvl;
	char	cwd[1024];

	pwd = getcwd(cwd, sizeof(cwd));
	shlvl = ft_itoa(1);
	env_add_back(&g_data.env, env_new(ft_strdup("PWD"), ft_strdup(pwd)));
	env_add_back(&g_data.env, env_new(ft_strdup("SHLVL"), shlvl));
}
int	main(int argc, char **argv, char **env)
{
	// atexit(ft_exit);

	g_data.env = NULL;
	if (!*env)
		fill_the_env();
	signal(SIGINT, sigusr_handler);
	signal(SIGQUIT, sigusr_handler);
	set_builtins();
	if (*env)
		g_data.env = fill_env(env);
	export("_=/usr/bin/env");
	if (argc != 1 && argv[1] != NULL)
		return (printf("Mamamia, don't use args\n"), 1);
	// g_data.path = ft_split(get_path(env), ':');
	// if (!g_data.path)
	// 	return (printf("ERROR\nthere is something with the path"), 1);
	while (1)
		display_prompt();
	return (0);
}
