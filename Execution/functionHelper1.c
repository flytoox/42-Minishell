/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functionHelper1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 23:11:34 by aait-mal          #+#    #+#             */
/*   Updated: 2023/07/21 01:27:13 by obelaizi         ###   ########.fr       */
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

void	which_fd(t_pars *parsed)
{
	if (parsed->in != -1)
		dup2(parsed->in, 0);
	if (parsed->out != -1)
		dup2(parsed->out, 1);
}

void	ft_print(const char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

int	fill_file(int fd, char *del)
{
	int		check;
	char	*line;

	check = 1;
	line = NULL;
	while (line || check)
	{
		if (!check)
			free(line);
		if (check)
			check = 0;
		line = get_next_line(0);
		if (line && ft_strlen(line) - 1 == ft_strlen(del)
			&& !ft_strncmp(del, line, ft_strlen(line) - 1))
		{
			free(line);
			break ;
		}
		ft_print(line, fd);
	}
	close(fd);
	return (open(".temp_file", O_RDONLY));
}

int	here_doc(char *del)
{
	int		in;
	char	***cmd_paths;
	int		pid;

	in = open(".temp_file", O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (in < 0)
		return (perror("Minishell"), exit(1), 1);
	in = fill_file(in, del);
	if (in < 0)
		return (perror("pipex"), exit(1), 1);
	return (0);
}
