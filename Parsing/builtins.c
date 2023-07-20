/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 20:55:59 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/20 01:28:11 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(char **args)
{
	int	i;
	int	j;
	int	flg;

	flg = 0;
	i = 0;
	j = 0;
	while (!ft_strncmp(args[j++], "-n", 2))
	{
		i = 0;
		while (args[0][++i] == 'n')
			;
		if (!args[0][i])
		{
			flg = 1;
			i = j;
		}
	}
	while (args[i + 1])
		printf("%s ", args[i++]);
	printf("%s", args[i]);
	if (!flg)
		printf("\n");
}

void	cd(char *path)
{
	if (chdir(path) == -1)
		perror("chdir");
}

void	pwd(void)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	// else
	// 	perror("getcwd");
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
