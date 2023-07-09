/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:15:43 by aait-mal          #+#    #+#             */
/*   Updated: 2023/07/09 15:26:49 by obelaizi         ###   ########.fr       */
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

typedef struct cmds
{
	char		*s;
	char		**flgs;
	struct cmds	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

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
	char	**path;
	char	*input;
	t_env	*env;
	t_cmd	*head;
	t_tkns	tkns;
}	t_data;

t_data	g_data;

t_env	*env_lstnew(char *key, char *value);
void	env_lstadd_back(t_env **lst, t_env *new);
int		count_char(const char *s, char c);
void	env_lstdelone(t_env *lst);
int		env_lstsize(t_env *lst);
void	env_lstclear(t_env **lst);

void	remove_quotes(char *str);
void	display_prompt(void);
void	parse(char *str);
int		count_str(const char *s, const char *s1);
char	**cust_split(char *s);
void	*ft_realloc(void *ptr, size_t size);
char	*get_name_var(char *argument);
char	*get_val_var(char *argument);

void	echo(char *str, int flag);
void	cd(char *path);
void	pwd(void);
void	export(char *argument);
void	unset(char *s);
void	env(void);

#endif
