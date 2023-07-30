/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 20:55:59 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/30 03:34:17 by obelaizi         ###   ########.fr       */
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
		return (g_data.exit_status = 1, perror("cd"));
	if (!getcwd(cwd, sizeof(cwd)))
	{
		printf("cd: error retrieving current directory: getcwd:\
 cannot access parent directories: No such file or directory\n");
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
			printf("Minishell: cd: HOME not set\n");
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
			printf("Minishell: cd: OLDPWD not set\n");
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

char	*get_val_var(char *argument)
{
	char	*vl_vr;

	if (!ft_strchr(argument, '='))
		return (NULL);
	vl_vr = ft_strchr(argument, '=') + 1;
	return (ft_strdup(vl_vr));
}

char	*get_name_var(char *argument)
{
	char	*nm_vr;
	char	*vl_vr;
	int		i;

	if (!ft_strchr(argument, '='))
		return (ft_strdup(argument));
	vl_vr = ft_strchr(argument, '=') + 1;
	i = -1;
	nm_vr = malloc(ft_strlen(argument) - ft_strlen(vl_vr));
	if (!nm_vr)
		exit(1);
	garbg_add_back(&g_data.garbage, garbg_new(nm_vr));
	while (argument[++i])
	{
		if (argument[i] == '=')
		{
			nm_vr[i] = '\0';
			break ;
		}
		nm_vr[i] = argument[i];
	}
	return (nm_vr);
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
