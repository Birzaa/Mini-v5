/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:16:30 by abougrai          #+#    #+#             */
/*   Updated: 2024/04/04 17:27:24 by abougrai         ###   ########.fr       */
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

char	**create_env(void)
{
	char	**envp;

	envp = NULL;
	envp = malloc(3 * (sizeof(char *)));
	if (!envp)
		return (perror(""), NULL);
	envp[0] = ft_strdup(PTH);
	if (!envp[0])
		return (ft_free_tab(envp), exit(1), (NULL));
	envp[1] = ft_strdup(_ENV);
	if (!envp[1])
		return (ft_free_tab(envp), exit(1), (NULL));
	envp[2] = NULL;
	return (envp);
}
