/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:18:45 by aait-mal          #+#    #+#             */
/*   Updated: 2023/07/31 01:49:57 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		garbg_clear(&g_data.garbage);
		exit (g_data.exit_status);
	}
	if (g_data.input[0])
		add_history(g_data.input);
	parse(g_data.input);
	free(g_data.input);
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
		}
		env_add_back(&new_env,
			env_new(name_var, val_var));
	}
	return (new_env);
}

void	fill_the_env(char **env)
{
	char	*pwd;
	char	*shlvl;
	char	cwd[1024];

	if (*env)
	{
		g_data.env = fill_env(env);
		return ;
	}
	pwd = getcwd(cwd, sizeof(cwd));
	shlvl = ft_itoa(1);
	env_add_back(&g_data.env, env_new(ft_strdup("PWD"), ft_strdup(pwd)));
	env_add_back(&g_data.env, env_new(ft_strdup("SHLVL"), shlvl));
}

int	main(int argc, char **argv, char **env)
{
	g_data.garbage = NULL;
	g_data.env = NULL;
	signal(SIGINT, sigusr_handler);
	signal(SIGQUIT, sigusr_handler);
	set_builtins();
	fill_the_env(env);
	if (argc != 1 && argv[1] != NULL)
		return (printf("Mamamia, don't use args\n"), 1);
	while (1)
		display_prompt();
	return (0);
}
