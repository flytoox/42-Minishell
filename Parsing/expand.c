/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 22:22:06 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/19 00:34:56 by obelaizi         ###   ########.fr       */
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
		if (!ft_strcmp(node->key, tmp))
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
		while (node->s[++i] && node->type != DELIM)
		{
			if ((node->s[i] == '\'' || node->s[i] == '"') && !flg)
				flg = i + 1;
			else if (flg && node->s[i] == node->s[flg - 1])
				flg = 0;
			else if (node->s[i] == '$' && node->s[i + 1] && (!flg || (flg && node->s[flg - 1] == '"')))
			{
				s3 = ft_substr(node->s, i, ft_strlen(node->s));
				trim_it(s3);
				s2 = env_value(&node->s[i]);
				node->s[i] = '\0';
				tmp = node->s;
				node->s = ft_strjoin(node->s, s2);
				tmp = node->s;
				node->s = ft_strjoin(node->s, s3);
			}
		}
		remove_quotes(node->s);
		node = node->next;
	}
}
