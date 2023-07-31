/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:15:43 by aait-mal          #+#    #+#             */
/*   Updated: 2023/07/31 01:44:00 by obelaizi         ###   ########.fr       */
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
# include <dirent.h>
# include <sys/stat.h>
# include <errno.h>

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

typedef struct garbage
{
	void			*ptr;
	struct garbage	*next;
}	t_grbg;

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
	int		quit_heredoc;
	t_grbg	*garbage;
}	t_data;

t_data	g_data;

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

t_grbg	*garbg_new(void *s);
void	garbg_add_back(t_grbg **lst, t_grbg *new);
void	garbg_front(t_grbg **lst, t_grbg *new);
int		garbg_size(t_grbg *lst);
void	garbg_clear(t_grbg **lst);

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
int		parse(char *str);
int		count_str(const char *s, const char *s1);
void	cust_split(char *s, t_cmd **cmds);
void	upgrade_splt(const char *sep);
char	*get_name_var(char *argument);
char	*get_val_var(char *argument);
int		is_syntax_error(void);
int		check_parse_export(char *s);
void	remove_quotes(t_pars *p);

void	echo(char **args);
void	cd(char *path);
void	pwd(void);
void	export(char *argument);
void	unset(char *s);
void	env(int is_env);
void	expand(t_pars *pars);
void	ft_exit(char **args, int is_child);

void	open_files(t_pars *tmp);
void	which_fd(t_pars *parsed);
int		here_doc(char *del, int is_expand);
void	trim_it(char *s);
char	*env_value(char *key, t_env *node);

char	*path_cmd(char *cmd, char *msg);
void	set_builtins(void);
void	execute(t_pars *parsed);
void	lunch_herdoc(t_pars *parsed);
bool	is_export(t_cmd *cmd);
void	tokens(void);
int		give_me_index(char **args);
void	make_the_path(void);
void	make_the_env(void);
char	**get_cmds_args(t_cmd *cmd, t_pars *parsed);
void	signals_handling(int status);
void	ft_print(const char *s, int fd);
void	close_fds(void);

#endif
