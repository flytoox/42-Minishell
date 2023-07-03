/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 20:55:59 by obelaizi          #+#    #+#             */
/*   Updated: 2023/06/12 11:38:58 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char *str, int flag)
{
	printf("%s", str);
	if (flag)
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

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd");
}

void	export(char *argument)
{
	char	*nm_vr;
	char	*vl_vr;
	int		i;
	char	*updt_vr;

	i = -1;
	nm_vr = argument;
	vl_vr = ft_strchr(argument, '=') + 1;
	while (g_data.env[++i])
	{
		if (!ft_strncmp(g_data.env[i], nm_vr, ft_strlen(nm_vr))
			&& g_data.env[i][ft_strlen(nm_vr)] == '=')
		{
			updt_vr = malloc(ft_strlen(nm_vr) + ft_strlen(vl_vr) + 2);
			g_data.env[i] = updt_vr;
			return ;
		}
	}
	updt_vr = malloc(ft_strlen(nm_vr) + ft_strlen(vl_vr) + 2);
	g_data.env[i] = updt_vr;
	g_data.env[i + 1] = NULL;
}

void	unset(char *s)
{
	int	i;
	int	j;

	i = -1;
	while (g_data.env[++i])
	{
		if (!ft_strncmp(g_data.env[i], s, ft_strlen(s))
			&& g_data.env[i][ft_strlen(s)] == '=')
		{
			j = i - 1;
			while (g_data.env[++j])
				g_data.env[j] = g_data.env[j + 1];
			return ;
		}
	}
}
