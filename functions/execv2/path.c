/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:37:01 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/02 13:33:24 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_tab_size(char **tab, int size)
{
	int i = 0;
	while (i < size)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**find_path(char **env)
{
	char	**path;
	int		i;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_split(env[i] + 5, ':');
			return (path);
		}
		i++;
	}
	return (path);
}

char	*valid_path(char **all_paths, char *cmd)
{
	int		i;
	char	*path;
	char	**valid_cmd;
	char	*full_path;

	full_path = NULL;
	if (!*cmd)
		return (cmd);
	valid_cmd = ft_split(cmd, ' ');
	i = 0;
	while (all_paths[i])
	{
		path = ft_strjoin(all_paths[i], "/");
		full_path = ft_strjoin(path, valid_cmd[0]);
		free(path);
		if (access(full_path, X_OK | F_OK) == 0)
		{
			ft_free_tab(valid_cmd);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_tab(valid_cmd);
	return (cmd);
}
