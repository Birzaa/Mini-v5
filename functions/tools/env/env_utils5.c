/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:45:35 by abougrai          #+#    #+#             */
/*   Updated: 2024/03/22 02:45:36 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_content_env(char *oldpwd, char *pwd)
{
	int	len_oldpwd;
	int	len_pwd;

	len_oldpwd = get_len_name(oldpwd);
	len_pwd = get_len_name(pwd);
	while (pwd[len_pwd])
		oldpwd[len_oldpwd++] = pwd[len_pwd++];
	oldpwd[len_oldpwd] = '\0';
}

int	check_value_env(char *var)
{
	int	i;

	i = 0;
	if (!ft_at_least_charset(var, "="))
		return (0);
	else if (ft_at_least_charset(var, "="))
	{
		while (var[i])
		{
			if (var[i] == '=' && var[i + 1] != '\0')
				return (1);
			i++;
		}
	}
	return (0);
}
