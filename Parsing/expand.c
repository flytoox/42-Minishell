/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 22:22:06 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/16 02:31:17 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*env_value(char *key)
{
	t_env	*node;
	char	*tmp;
	int		i;

	node = g_data.env;
	printf("Key = %s\n", key);
	key++;
	tmp = malloc(ft_strlen(key) + 1);
	i = 0;
	while (key[i] && (ft_isalnum(key[i]) || key[i] == '_'))
	{
		printf("---> %c\n", key[i]);
		tmp[i] = key[i];
		i++;
	}
	tmp[i] = '\0';
	printf("tmp = %s\n", tmp);
	while (node)
	{
		if (!ft_strncmp(node->key, tmp, ft_strlen(tmp)))
			return (free(tmp), node->value);
		node = node->next;
	}
	return (free(tmp), ft_strdup(""));
}

void	trim_it(char *s)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (s[++i] && (ft_isalnum(s[i]) || s[i] == '_'))
		;
	while (s[i])
		s[++j] = s[i++];
	s[++j] = '\0';
}

void	expand(t_cmd *node)
{
	char	*s2;
	char	*s3;
	int		i;
	int		flg;
	char	*tmp;

	while (node)
	{
		flg = 0;
		i = -1;
		if (node->quote == SQ)
		{
			node = node->next;
			continue ;
		}
		while (node->s[++i])
		{
			if ((node->s[i] == '\'' || node->s[i] == '"') && !flg)
				flg = i + 1;
			else if (flg && node->s[i] == node->s[flg - 1])
				flg = 0;
			else if (node->s[i] == '$' && (node->quote == DQ || !flg || (flg && node->s[flg - 1] == '"')))
			{
				s3 = ft_substr(node->s, i, ft_strlen(node->s));
				trim_it(s3);
				printf("s3 = %s\n", s3);
				s2 = env_value(&node->s[i]);
				printf("s2 = %s\n", s2);
				node->s[i] = '\0';
				tmp = node->s;
				printf("node->s = %s\n", node->s);
				node->s = ft_strjoin(node->s, s2);
				// free(tmp);
				// free(s2);
				tmp = node->s;
				node->s = ft_strjoin(node->s, s3);
				// free(tmp);
				// free(s3);
				printf("TRUE\n");
			}
		}
		node = node->next;
	}
}
