/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:18:45 by aait-mal          #+#    #+#             */
/*   Updated: 2023/07/08 22:27:58 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigusr_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	display_prompt(void)
{
	rl_catch_signals = 0;
	g_data.input = readline("\033[0;32mminishell# \033[0m");
	if (!g_data.input)
	{
		env_lstclear(&g_data.env);
		free_dbl_pntr((void **)g_data.path);
		exit (0);
	}
	parse(g_data.input);
	free(g_data.input);
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

	new_env = NULL;
	i = 0;
	while (env[++i])
		env_lstadd_back(&new_env,
			env_lstnew(get_name_var(env[i]), get_val_var(env[i])));
	return (new_env);
}

int	main(int argc, char **argv, char **env)
{
	atexit(ft_exit);
	signal(SIGINT, sigusr_handler);
	signal(SIGQUIT, sigusr_handler);
	g_data.env = fill_env(env);
	if (argc != 1 && argv[1] != NULL)
		return (printf("Mamamia, don't use args\n"), 1);
	g_data.path = ft_split(get_path(env), ':');
	if (!g_data.path)
		return (printf("ERROR\nthere is something with the path"), 1);
	while (1)
		display_prompt();
	return (0);
}
