/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:15:43 by aait-mal          #+#    #+#             */
/*   Updated: 2023/07/24 01:38:24 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "Libft/libft.h"

# define CMD_NT_FND " command not found\n"
# define NO_SUCH_FILE " No such file or directory\n"
# define FILE_NOT_FOUND -3
# define FD_INIT -2

enum e_type
{
	PIPE,
	HEREDOC,
	DELIM,
	APPEND,
	OUT,
	IN,
	FD,
	CMD,
};

enum e_quotes
{
	F,
	T,
};

typedef struct cmds
{
	char			*s;
	enum e_type		type;
	enum e_quotes	quote;
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
	struct parsing	*next;
	struct parsing	*prev;
	int				out;
	int				in;

}	t_pars;

typedef struct minikhell
{
	char	**path;
	char	**env_tab;
	char	*input;
	t_env	*env;
	t_cmd	*cmds;
	t_pars	*pars;
	int		not_found;
	char	**builtins;
	int		exit_status;
}	t_data;

extern t_data g_data;

void	sigusr_handler(int signum);

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
void	make_cmd_prev(void);
void	make_pars_prev(void);

t_pars	*parse_new(t_cmd *cmd);
void	parse_add_back(t_pars **lst, t_pars *new);
int		parse_size(t_pars *lst);
void	parse_clear(t_pars **lst);
void	parse_front(t_pars **lst, t_pars *new);

int		is_closed(const char *s);

void	display_prompt(void);
void	rmv_frst_chr(char *s, int i);
void	parse(char *str);
int		count_str(const char *s, const char *s1);
void	cust_split(char *s);
void	upgrade_splt(const char *sep);
char	*get_name_var(char *argument);
char	*get_val_var(char *argument);
int		is_syntax_error(void);
int		check_parse_export(char *s);
void	remove_quotes(char *s);

void	echo(char **args);
void	cd(char *path);
void	pwd(void);
void	export(char *argument);
void	unset(char *s);
void	env(int is_env);
void	expand(t_cmd *node);
void	open_files(void);
void	which_fd(t_pars *parsed);
int		here_doc(char *del, int is_expand);
void	trim_it(char *s);
char	*env_value(char *key);

char	*get_next_line(int fd);

char	*path_cmd(char *cmd, char *msg);
void	set_builtins(void);
void	execute(void);

#endif
