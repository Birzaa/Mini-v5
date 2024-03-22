/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:45:24 by abougrai          #+#    #+#             */
/*   Updated: 2024/03/22 02:45:25 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_multiple_env(t_env *env1, t_env *env2)
{
	free_env(env1);
	free_env(env2);
}

int	get_len_name(char *n)
{
	int	i;

	i = 0;
	while (n[i] != '=')
		i++;
	return (i);
}

char	*ft_strcpy_content_env(char *s1, char *s2, char *n)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (n[j])
		s1[i++] = n[j++];
	while (s2[k])
		s1[i++] = s2[k++];
	s1[i] = '\0';
	return (s1);
}

void	print_pwd_env(void)
{
	char	*pwd;

	pwd = NULL;
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (perror(""));
		ft_putstr_fd("PWD=", 1);
		ft_putstr_fd(pwd, 1);
		ft_putchar_fd('\n', 1);
		free(pwd);
	}
}

int	get_len_to_equal(char *content)
{
	int	i;

	i = 0;
	if (!ft_at_least_charset(content, "="))
		return (ft_strlen(content));
	while (content[i] != '=')
		i++;
	return (i);
}
