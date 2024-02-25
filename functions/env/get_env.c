/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:16:30 by abougrai          #+#    #+#             */
/*   Updated: 2024/02/25 10:46:33 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_env(char **env)
{
	int		i;
	t_env	*envp;
	t_env	*tmp;

	i = 0;
	envp = NULL;
	tmp = NULL;
	while (env[i])
	{
		tmp = ft_env_new(env[i], 0);
		if (!tmp)
		{
			free_env(envp);
			return (NULL);
		}
		add_back_env(&envp, tmp);
		i++;
	}
	refresh_env(envp);
	return (envp);
}

t_env	*create_env(void)
{
	t_env	*env;

	env = NULL;
	env = create_env_part1(env);
	if (!env)
		return (NULL);
	/* env = create_env_part2(env);
	{
		free_env(env);
		return (NULL);
	} */
	return (env);
}
t_env	*create_env_part1(t_env *env)
{
	t_env	*tmp;
	char	*pwd;
	char	*newpwd;

	env = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	newpwd = ft_strjoin("PWD=", pwd);
	if (!newpwd)
	{
		return (NULL);
		free(pwd);
	}
	free(pwd);
	tmp = ft_env_new(newpwd, 1);
	if (!tmp)
	{
		free(newpwd);
		return (NULL);
	}
	add_back_env(&env, tmp);
	free(newpwd);
	return (env);
}

/* t_env	*create_env_part2(t_env *env)
{
	t_env	*tmp;

	tmp = ft_env_new(ft_strdup(COLORS_ENV), 1);
	add_back_env(&env, tmp);
	tmp = ft_env_new(ft_strdup(SHLVL_ENV), 1);
	add_back_env(&env, tmp);
	tmp = ft_env_new(ft_strdup(PATH_ENV), 1);
	add_back_env(&env, tmp);
	tmp = ft_env_new(ft_strdup(_ENV), 1);
	add_back_env(&env, tmp);
	return (env);
} */