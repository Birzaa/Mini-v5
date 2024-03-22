/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tab_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:43:12 by abougrai          #+#    #+#             */
/*   Updated: 2024/03/22 02:43:13 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_tab_env(t_env *env)
{
	char	**tab_env;
	char	*temp;
	t_env	*tmp;
	int		tab_size;
	int		i;

	i = 0;
	tmp = env;
	tab_size = ft_envsize(env);
	tab_env = malloc((tab_size + 1) * sizeof(char *));
	if (!tab_env)
		return (NULL);
	while (tmp)
	{
		temp = ft_strdup(tmp->content);
		if (!temp)
			return (ft_free_tab(tab_env), NULL);
		tab_env[i++] = temp;
		tmp = tmp->next;
	}
	tab_env[i] = NULL;
	return (tab_env);
}
