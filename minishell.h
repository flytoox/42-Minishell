/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:15:43 by aait-mal          #+#    #+#             */
/*   Updated: 2023/07/14 21:45:53 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "Libft/libft.h"

enum e_type
{
	PIPE = 1,
	HEREDOC,
	APPEND,
	OUT,
	IN,
	FD,
	CMD,
};

enum e_quote
{
	NONE = 0,
	SQ,
	DQ,
};
typedef struct cmds
{
	char			*s;
	enum e_type		type;
	enum e_quote	quote;
	struct cmds		*next;
	struct cmds		*prev;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct parsing
{
	t_cmd			*cmd;
	int				out;
	int				in;
	struct parsing	*next;
}	t_pars;

typedef struct minikhell
{
	char	**path;
	char	*input;
	t_env	*env;
	t_cmd	*cmds;
	t_pars	*pars;
}	t_data;

t_data	g_data;

t_env	*env_new(char *key, char *value);
void	env_add_back(t_env **lst, t_env *new);
void	env_delone(t_env *lst);
int		env_size(t_env *lst);
void	env_clear(t_env **lst);

t_cmd	*cmd_new(char *s);
void	cmd_add_back(t_cmd **lst, t_cmd *new);
void	cmd_front(t_cmd **lst, t_cmd *new);
int		cmd_size(t_cmd *lst);
void	cmd_clear(t_cmd **lst);
void	make_it_prev(void);

int		is_closed(const char *s);
void	remove_quotes(void);
void	display_prompt(void);
void	parse(char *str);
int		count_str(const char *s, const char *s1);
void	cust_split(char *s);
void	upgrade_splt(const char *sep);
char	*get_name_var(char *argument);
char	*get_val_var(char *argument);
int		is_syntax_error(void);

void	echo(char *str, int flag);
void	cd(char *path);
void	pwd(void);
void	export(char *argument);
void	unset(char *s);
void	env(void);
void	expand(void);

void	execute(void);

#endif
