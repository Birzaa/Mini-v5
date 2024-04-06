/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:43:24 by abougrai          #+#    #+#             */
/*   Updated: 2024/04/06 23:24:51 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_check(t_env *env, char *s, int check)
{
	int	len_s;
	int	len;

	len = get_len_to_equal(env->content);
	len_s = get_len_to_equal(s);
	if (env->next)
	{
		if (!(ft_strncmp(env->content, s, len_s) && len == len_s && check)
			|| (!ft_strncmp(env->content, s, len_s) && len == len_s && !check))
			swap_content_env(env, env->next);
	}
}

void	unset_del(t_env *env, char *s)
{
	t_env	*prev;
	t_env	*t;
	int		len_s;
	int		t_len;
	int		check;

	check = 0;
	len_s = get_len_to_equal(s);
	if (ft_at_least_charset(s, "="))
		check = 1;
	unset_check(env, s, check);
	prev = env;
	t = env->next;
	while (t)
	{
		t_len = get_len_to_equal(t->content);
		if (!ft_strncmp(t->content, s, len_s) && t_len == len_s && check)
			return (del_node_env(t, prev));
		else if (!ft_strncmp(t->content, s, len_s) && t_len == len_s && !check)
			return (del_node_env(t, prev));
		t = t->next;
		prev = prev->next;
	}
}

void	while_unset(t_env *env, char *command)
{
	if (!ft_strncmp("_", command, 2))
		return ;
	else if (ft_envsize(env) == 1)
		return ;
	else
		unset_del(env, command);
}

void	ft_unset(t_env *env, char **command)
{
	int	i;

	i = 1;
	if (!command[i])
		return ;
	else if (command[i])
		while (command[i])
			while_unset(env, command[i++]);
	g_sig.status = 0;
}
