/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functionsHelpers1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 23:11:34 by aait-mal          #+#    #+#             */
/*   Updated: 2023/08/06 18:13:42 by obelaizi         ###   ########.fr       */
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
	if (sig == SIGINT)
	{
		rl_done = 1;
		g_data.quit_heredoc = 1;
		g_data.exit_status = 130;
	}
}

void	fill_file(int fd[2], char *del, int is_expand, char *line)
{
	while (line)
	{
		line = readline("> ");
		if (!line || g_data.quit_heredoc)
		{
			if (g_data.quit_heredoc)
			{
				free(line);
				close(fd[1]);
				close(fd[0]);
				pipe(fd);
			}
			break ;
		}
		garbg_add_back(&g_data.garbage, garbg_new(line));
		if (line && ft_strlen(line) == ft_strlen(del)
			&& !ft_strcmp(del, line))
			break ;
		if (!is_expand)
			line = expand_her(line);
		ft_print(line, fd[1]);
	}
}

int	here_doc(char *del, int is_expand)
{
	int		fd[2];

	if (pipe(fd) < 0)
		return (perror("minishell"), exit(1), 1);
	rl_event_hook = event;
	signal(SIGINT, herdoc_signal_handler);
	if (g_data.quit_heredoc)
		return (close(fd[1]), fd[0]);
	fill_file(fd, del, is_expand, ft_strdup(""));
	close(fd[1]);
	return (fd[0]);
}
