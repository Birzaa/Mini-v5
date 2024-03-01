/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:16:30 by abougrai          #+#    #+#             */
/*   Updated: 2024/03/01 09:19:02 by abougrai         ###   ########.fr       */
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
		tmp = ft_env_new(env[i]);
		if (!tmp)
		{
			free_env(envp);
			return (NULL);
		}
		add_back_env(&envp, tmp);
		i++;
	}
	return (envp);
}

t_env	*create_env(void)
{
	int		error;
	t_env	*env;

	error = 0;
	env = NULL;
	env = create_env_part1(env);
	if (!env)
		return (NULL);
	create_env_part2(&env, &error);
	if (error)
	{
		free_env(env);
		return (NULL);
	}
	return (env);
}

t_env	*create_env_part1(t_env *env)
{
	t_env	*tmp;
	char	*pwd;
	char	*newpwd;

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
	tmp = ft_env_new(newpwd);
	if (!tmp)
	{
		free(newpwd);
		return (NULL);
	}
	add_back_env(&env, tmp);
	return (env);
}

void	create_env_part2(t_env **env, int *error)
{
	t_env	*tmp1;
	t_env	*tmp2;
	t_env	*tmp3;
	t_env	*tmp4;

	tmp2 = NULL;
	tmp3 = NULL;
	tmp4 = NULL;
	tmp1 = ft_env_new(ft_strdup(OLDPWD_ENV));
	add_back_env(env, tmp1);
	tmp2 = ft_env_new(ft_strdup(SHLVL_ENV));
	add_back_env(env, tmp2);
	tmp3 = ft_env_new(ft_strdup(PTH));
	add_back_env(env, tmp3);
	tmp4 = ft_env_new(ft_strdup(_ENV));
	add_back_env(env, tmp4);
	if (tmp1 || tmp2 || tmp3 || tmp4)
		(*error) = 1;
}
