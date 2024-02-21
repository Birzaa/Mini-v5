/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:16:30 by abougrai          #+#    #+#             */
/*   Updated: 2024/02/21 16:55:43 by abougrai         ###   ########.fr       */
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
		ft_env_add_back(&envp, tmp);
		i++;
	}
	print_env(envp);
	return (envp);
}
