/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 20:55:59 by obelaizi          #+#    #+#             */
/*   Updated: 2023/08/03 17:10:21 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(char **args)
{
	int	i;
	int	j;
	int	flg;

	flg = 0;
	j = -1;
	while (!ft_strncmp(args[++j], "-n", 2))
	{
		i = 0;
		while (args[j][++i] == 'n')
			;
		if (!args[j][i])
			flg = 1;
		else
			break ;
	}
	i = j;
	while (args[i + 1])
		printf("%s ", args[i++]);
	printf("%s", args[i]);
	if (!flg)
		printf("\n");
}

void	cd_helper(t_env *node, char *path)
{
	char	oldpwd[1024];
	char	cwd[1024];

	getcwd(oldpwd, sizeof(oldpwd));
	if (chdir(path) == -1)
		return (g_data.exit_status = 1, ft_perror("cd: ",
				path, strerror(errno)));
	if (!getcwd(cwd, sizeof(cwd)))
	{
		ft_print("cd: error retrieving current directory: getcwd:\
 cannot access parent directories: No such file or directory", 2);
		return ;
	}
	if (!env_value("OLDPWD", g_data.env))
		env_add_back(&g_data.env, env_new("OLDPWD", oldpwd));
	while (node)
	{
		if (!ft_strcmp(node->key, "PWD"))
			node->value = ft_strdup(cwd);
		else if (!ft_strcmp(node->key, "OLDPWD"))
			node->value = ft_strdup(oldpwd);
		node = node->next;
	}
}

void	cd(char *path)
{
	if (!ft_strcmp(path, "") || !ft_strcmp(path, "~"))
	{
		path = env_value("HOME", g_data.env);
		if (!path)
		{
			g_data.exit_status = 1;
			ft_print("minishell: cd: HOME not set", 2);
			return ;
		}
		else if (!*path)
			return ;
	}
	else if (!ft_strcmp(path, "-"))
	{
		path = env_value("OLDPWD", g_data.env);
		if (path)
			printf("%s\n", path);
		if (!path)
		{
			g_data.exit_status = 1;
			ft_print("minishell: cd: OLDPWD not set", 2);
			return ;
		}
	}
	cd_helper(g_data.env, path);
}

void	pwd(void)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
}

int	check_parse_export(char *s)
{
	int		i;

	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (1);
	i = 0;
	while (s[i] && s[i] != '=')
	{
		if ((!ft_isalnum(s[i]) && s[i] != '_' && s[i] != '+')
			|| (s[i] == '+' && s[i + 1] != '='))
			return (1);
		i++;
	}
	return (0);
}
