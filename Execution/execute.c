/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 01:47:36 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/31 01:42:40 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	edge_cases(int i, int j)
{
	if (i == 6 && j == 1)
		env(0);
	else if (i == 2 && j == 1)
		env(1);
	else if (i == 5 && j == 1)
		cd("");
	else if (!i)
		printf("\n");
	return (1);
}

int	check_builtins(char ***targs, int is_child, char **args)
{
	int		i;
	int		j;

	i = give_me_index(args);
	if (!g_data.builtins[i] || (!is_child && i < 3) || (is_child && i > 3))
		return (0);
	j = -1;
	while (args[++j])
	{
		if (i == 0 && j)
			return (echo(args + 1), 1);
		else if (i == 1)
			return (pwd(), 1);
		else if (i == 2 && j)
			return (*targs = *targs + 1, 2);
		else if (i == 3)
			return (ft_exit(&args[j + 1], is_child), 0);
		else if (i == 4 && j)
			unset(args[j]);
		else if (i == 5 && j)
			return (cd(args[j]), 1);
		else if (i == 6 && j)
			export(args[j]);
	}
	return (edge_cases(i, j));
}

int	helper_function(t_pars *parsed, int fd[2], int tmp, char ***args)
{
	int	ret;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (parsed->next && parsed->out == FD_INIT)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
	}
	if (parsed->prev && parsed->in == FD_INIT)
	{
		close(fd[1]);
		dup2(tmp, 0);
		close(tmp);
		close(fd[0]);
	}
	which_fd(parsed);
	ret = check_builtins(args, 1, *args);
	if (ret == 1)
	{
		garbg_clear(&g_data.garbage);
		exit(0);
	}
	return (make_the_path(), make_the_env(), ret);
}

void	execute_child(int *tmp, int fd[2], t_pars *parsed, char **args)
{
	if (pipe(fd) == -1)
		return (perror("pipe"));
	if (*tmp == -2)
		*tmp = fd[0];
	if (fork() == 0)
	{
		if (helper_function(parsed, fd, *tmp, &args) == 2)
			args[0] = path_cmd(args[0], NO_SUCH_FILE);
		else
			args[0] = path_cmd(args[0], CMD_NT_FND);
		execve(args[0], args, g_data.env_tab);
		perror("minishell");
		garbg_clear(&g_data.garbage);
		exit(127);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		if (*tmp != fd[0])
			close(*tmp);
		*tmp = fd[0];
		close(fd[1]);
	}
}

void	execute(t_pars *parsed)
{
	int		on_child;
	char	**args;
	int		fd[2];
	int		tmp;

	tmp = -2;
	on_child = 0;
	signal(SIGINT, SIG_IGN);
	while (parsed)
	{
		args = get_cmds_args(parsed->cmd, parsed);
		if (args && !check_builtins(&args, 0, args)
			&& parsed->in != FILE_NOT_FOUND)
		{
			on_child = 1;
			execute_child(&tmp, fd, parsed, args);
		}
		parsed = parsed->next;
	}
	if (tmp != -2)
		close(tmp);
	signals_handling(on_child);
	close_fds();
	unlink(".temp_file");
}
