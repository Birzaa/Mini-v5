/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:45:30 by abougrai          #+#    #+#             */
/*   Updated: 2024/04/11 04:46:47 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env, int fd)
{
	refresh_env(env, 0);
	if (!env->content && !env->next)
		return ;
	while (env)
	{
		if (!ft_at_least_charset(env->content, "="))
			ft_nothing();
		else
		{
			ft_putstr_fd(env->content, fd);
			ft_putchar_fd('\n', fd);
		}
		env = env->next;
	}
}

t_env	*ft_env_last(t_env *env)
{
	while (env)
	{
		if (!env->next)
			return (env);
		env = env->next;
	}
	return (env);
}

t_env	*ft_env_new(void *content)
{
	t_env	*elem;

	elem = malloc(sizeof(t_env));
	if (!elem)
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	elem->exported = 0;
	return (elem);
}

void	add_back_env(t_env **env, t_env *new)
{
	t_env	*last;

	if (!*env)
		*env = new;
	else
	{
		last = ft_env_last(*env);
		last->next = new;
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	tmp = NULL;
	if (!env)
		return ;
	while (env)
	{
		if (env->exported)
			free(env->content);
		tmp = env;
		env = env->next;
		free(tmp);
	}
}
