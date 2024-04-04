/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 08:11:45 by abougrai          #+#    #+#             */
/*   Updated: 2024/04/04 10:21:12 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_export_join_content(t_env *env, char *content)
{
	t_env	*tmp;
	int		len_c;
	int		len_tmp;

	len_tmp = 0;
	len_c = get_len_to_equal(content);
	tmp = env;
	while (tmp)
	{
		len_tmp = get_len_to_equal(tmp->content);
		if (!ft_strncmp(tmp->content, content, len_c) && len_tmp == len_c)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (0);
}

t_env	*ft_get_target_export(t_env *env, char *content)
{
	t_env	*tmp;
	int		len_c;
	int		len_tmp;

	len_tmp = 0;
	len_c = get_len_to_equal(content);
	tmp = env;
	while (tmp)
	{
		len_tmp = get_len_to_equal(tmp->content);
		if (!ft_strncmp(tmp->content, content, len_c) && len_tmp == len_c)
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

void	export_new_add_back_add(t_env **env, char *join)
{
	t_env	*tmp;

	tmp = NULL;
	tmp = ft_env_new_export_add(join);
	if (!tmp)
		return (perror(""), free(join));
	add_back_env(env, tmp);
	return ;
}

t_env	*ft_env_new_export_add(void *join)
{
	t_env	*elem;

	elem = malloc(sizeof(t_env));
	if (!elem)
		return (NULL);
	elem->content = join;
	elem->next = NULL;
	elem->exported = 1;
	return (elem);
}
