/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:45:21 by abougrai          #+#    #+#             */
/*   Updated: 2024/04/04 08:25:31 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_sort_env(t_env *env, int (*cmp)(char *, char *))
{
	char	*str;
	t_env	*tmp;

	tmp = env;
	while (env->next)
	{
		if (((*cmp)(env->content, env->next->content)) >= 0)
		{
			str = env->content;
			env->content = env->next->content;
			env->next->content = str;
			env = tmp;
		}
		else
			env = env->next;
	}
	env = tmp;
	return (env);
}

int	ft_envsize(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

void	del_node_env(t_env *target, t_env *previous)
{
	if (!target->next)
	{
		previous->next = NULL;
		if (target->exported && target->content)
			free(target->content);
		free(target);
	}
	else
	{
		previous->next = target->next;
		if (target->exported)
			free(target->content);
		free(target);
	}
}

void	swap_content_env(t_env *node1, t_env *node2)
{
	char	*tmp;
	int		exported;

	exported = node1->exported;
	node1->exported = node2->exported;
	node2->exported = exported;
	tmp = node1->content;
	node1->content = node2->content;
	node2->content = tmp;
}

void	pop_node_env(t_env *env)
{
	t_env	*tmp;

	if (env)
	{
		tmp = env;
		env = env->next;
		free(tmp);
	}
}
