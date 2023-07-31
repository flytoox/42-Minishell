/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functionsHelpers1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 23:11:34 by aait-mal          #+#    #+#             */
/*   Updated: 2023/07/31 01:12:46 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			s2 = env_value(&s[i], g_data.env);
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
	char	*line;

	line = ft_strdup("");
	rl_event_hook = event;
	g_data.quit_heredoc = 0;
	signal(SIGINT, herdoc_signal_handler);
	while (line)
	{
		free(line);
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
	return (close(fd), open(".temp_file", O_RDONLY));
}

int	here_doc(char *del, int is_expand)
{
	int		in;

	in = open(".temp_file", O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (in < 0)
		return (perror("Minishell"), exit(1), 1);
	in = fill_file(in, del, is_expand);
	if (in < 0)
		return (perror("Minishell"), exit(1), 1);
	return (in);
}
