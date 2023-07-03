/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:15:43 by aait-mal          #+#    #+#             */
/*   Updated: 2023/06/24 12:46:57 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include "Libft/libft.h"

typedef struct cmds
{
	char		*s;
	char		*flg;
	struct cmds	*next;
}	t_cmd;

typedef struct tkns
{
	int	pipe;
	int	heredoc;
	int	append;
	int	out;
	int	in;
}	t_tkns;

typedef struct minikhell
{
	char	**env;
	t_cmd	*head;
	t_tkns	tkns;
}	t_data;

t_data	g_data;

void	display_prompt(void);
void	parse(char *str);
int		count_str(const char *s, const char *s1);

#endif
