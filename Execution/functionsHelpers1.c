/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functionsHelpers1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 23:11:34 by aait-mal          #+#    #+#             */
/*   Updated: 2023/08/03 21:30:16 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_her(char *s)
{
	char	*s3;
	char	*s2;
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
			if (s2)
				s = ft_strjoin(s, s2);
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
		g_data.exit_status = 130;
		fd = open("/tmp/temp_file", O_CREAT | O_TRUNC | O_WRONLY, 0777);
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
		line = readline("> ");
		if (!line || g_data.quit_heredoc)
		{
			if (line)
				free(line);
			break ;
		}
		garbg_add_back(&g_data.garbage, garbg_new(line));
		if (line && ft_strlen(line) == ft_strlen(del)
			&& !ft_strcmp(del, line))
			break ;
		if (!is_expand)
			line = expand_her(line);
		ft_print(line, fd);
	}
	return (close(fd), open("/tmp/temp_file", O_RDONLY));
}

int	here_doc(char *del, int is_expand)
{
	int		in;

	in = open("/tmp/temp_file", O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (in < 0)
		return (perror("minishell"), exit(1), 1);
	in = fill_file(in, del, is_expand);
	if (in < 0)
		return (perror("minishell"), exit(1), 1);
	return (in);
}
