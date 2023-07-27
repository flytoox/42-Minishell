/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functionHelper1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 23:11:34 by aait-mal          #+#    #+#             */
/*   Updated: 2023/07/27 22:49:56 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_cmd_helper(char *cmd, char *tmp2, char *msg)
{
	int			i;
	char		*tmp;

	i = 0;
	tmp = 0;
	if (!ft_strcmp(cmd, "."))
		return (printf("minishell: .: filename argument required\n.:\
usage: . filename [arguments]\n"), exit(2), NULL);
	else if (!ft_strcmp(cmd, ".."))
		return (printf("Minishell: %s%s", cmd, msg), exit(127), NULL);
	if (!cmd[0] || !g_data.path)
		return (printf("Minishell: %s%s", cmd, msg), exit(127), NULL);
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
	return (NULL);
}

char	*path_cmd(char *cmd, char *msg)
{
	struct stat	statbuf;
	char		*tmp2;

	tmp2 = path_cmd_helper(cmd, cmd, msg);
	if (tmp2)
		return (tmp2);
	tmp2 = cmd;
	if (stat(tmp2, &statbuf) == 0)
	{
		if (S_ISREG(statbuf.st_mode))
		{
			if (access(tmp2, X_OK) == 0) 
				return (tmp2);
		}
		else if (S_ISDIR(statbuf.st_mode)) 
			return (printf("minishell : %s: is a directory\n", tmp2)
				, exit(126), NULL);
	}
	else
		if (errno == EACCES) 
			return (printf("minishell: %s: Permission denied\n", tmp2),
				exit(126), NULL);
	return (printf("Minishell: %s%s", tmp2, msg), exit(127), NULL);
}

void	which_fd(t_pars *parsed)
{
	if (parsed->in != FD_INIT)
		dup2(parsed->in, 0);
	if (parsed->out != FD_INIT)
		dup2(parsed->out, 1);
}

void	ft_print(const char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

char	*expand_her(char *s)
{
	char	*s3;
	char	*s2;
	char	*tmp;
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			i++;
			s3 = ft_substr(s, i, ft_strlen(s));
			trim_it(s3);
			s2 = env_value(&s[i]);
			s[i - 1] = '\0';
			tmp = s;
			if (s2)
				s = ft_strjoin(s, s2);
			tmp = s;
			s = ft_strjoin(s, s3);
		}
		i++;
	}
	return (s);
}

int	event(void)
{
	return (0);
}

void	herdoc_signal_handler(int sig)
{
	int	fd;

	if (sig == SIGINT)
	{
		rl_done = 1;
		g_data.quit_heredoc = 1;
		fd = open(".temp_file", O_CREAT | O_TRUNC | O_WRONLY, 0777);
		close(fd);
	}
}

int	fill_file(int fd, char *del, int is_expand)
{
	int		check;
	char	*line;

	check = 1;
	line = NULL;
	rl_event_hook = event;
	g_data.quit_heredoc = 0;
	signal(SIGINT, herdoc_signal_handler);
	while (line || check)
	{
		if (!check)
			free(line);
		if (check)
			check = 0;
		line = readline("> ");
		if (!line || g_data.quit_heredoc)
			break ;
		if (line && ft_strlen(line) == ft_strlen(del)
			&& !ft_strcmp(del, line))
		{
			free(line);
			break ;
		}
		if (!is_expand)
			line = expand_her(line);
		ft_print(line, fd);
	}
	g_data.quit_heredoc = 0;
	close(fd);
	return (open(".temp_file", O_RDONLY));
}

int	here_doc(char *del, int is_expand)
{
	int		in;
	int		pid;

	in = open(".temp_file", O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (in < 0)
		return (perror("Minishell"), exit(1), 1);
	in = fill_file(in, del, is_expand);
	if (in < 0)
		return (perror("Minishell"), exit(1), 1);
	return (in);
}
