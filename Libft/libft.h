/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:02:29 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/31 01:33:23 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "../minishell.h"

size_t	ft_strlen(const char *s);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t size);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *str);
char	*ft_strdup(const char *src);

char	**ft_split(char const *s, char c);
void	free_dbl_pntr(void **str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, const char *s2);
char	*ft_itoa(int n);

#endif