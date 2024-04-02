/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:43:17 by abougrai          #+#    #+#             */
/*   Updated: 2024/04/02 11:55:58 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_cd(char *new_cmd, char *home, char *tmp)
{
	printf("bash: cd: %s: No such file or directory\n", new_cmd);
	g_sig.status = 1;
	return (free(new_cmd), free(home), free(tmp));
}

void	ft_cd_tild(t_data *data, char *command)
{
	char	*new_cmd;
	char	*tmp;
	char	*home;

	home = NULL;
	new_cmd = "";
	if ((ft_is_home_set(data->env)))
	{
		home = ft_getenv(data->env, "HOME");
		if (!home)
			return (perror(""));
		tmp = ft_strjoin(&home[5], command);
		if (!tmp)
			return (perror(""), free(home));
		new_cmd = ft_strjoin(new_cmd, tmp);
		if (!new_cmd)
			return (perror(""), free(home), free(tmp));
		else if (chdir(new_cmd))
		{
			error_cd(new_cmd, home, tmp);
			return ;
		}
		g_sig.status = 0;
		return (free(new_cmd), free(home), free(tmp));
	}
}

void	home_not_set(void)
{
	printf("bash: cd: HOME not set\n");
	g_sig.status = 1;
}

void	ft_cd_home(t_data *data, char *command)
{
	char	*home;
	char	*tmp;

	home = NULL;
	if ((ft_is_home_set(data->env)))
	{
		home = ft_getenv(data->env, "HOME");
		if (!home)
			return (perror(""));
		if (!check_value_env(home))
			return (free(home));
		else if (chdir(&home[5]))
		{
			tmp = ft_strjoin(&home[5], command);
			if (!tmp)
				return (perror(""), free(home));
			printf("bash: cd: %s: No such file or directory\n", tmp);
			g_sig.status = 1;
			return (free(tmp), free(home));
		}
		free(home);
		g_sig.status = 0;
	}
	else
		home_not_set();
}

void	ft_cd(t_data *data, char **command)
{
	refresh_env(data->env, 1);
	if (!command[1] || command[1][0] == '\0')
		return ;
	else if (command[2])
	{
		g_sig.status = 1;
		return (ft_putstr_fd("bash: cd: too many arguments\n", 1));
	}
	else if (!ft_strncmp(command[1], "~", 2))
		return (ft_cd_home(data, command[1]));
	else if (!ft_strncmp(command[1], "~/", 2))
		return (ft_cd_tild(data, command[1]));
	if (chdir(command[1]) != 0)
	{
		printf("bash: cd: %s: No such file or directory\n", command[1]);
		g_sig.status = 1;
	}
}
