/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:43:17 by abougrai          #+#    #+#             */
/*   Updated: 2024/04/07 01:21:01 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_cd(char *new_cmd, char *home, char *tmp)
{
	handle_error_cd(new_cmd, strerror(errno));
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
	g_sig.status = 0;
	if ((ft_is_home_set(data->env)))
	{
		home = ft_getenv(data->env, "HOME");
		if (!home)
			return (perror(""));
		tmp = ft_strjoin(&home[5], ++command);
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
		return (free(new_cmd), free(home), free(tmp));
	}
}

void	home_not_set(void)
{
	ft_putstr_fd("bash: cd: HOME not set\n", 2);
	g_sig.status = 1;
}

void	ft_cd_home(t_data *data, char *command)
{
	char	*home;
	char	*tmp;

	tmp = NULL;
	home = NULL;
	if ((ft_is_home_set(data->env)))
	{
		home = ft_getenv(data->env, "HOME");
		if (!home)
			return (perror(""));
		if (!check_value_env(home))
			return (free(home));
		else if (chdir(&home[5]))
			ft_error_cd(tmp, command, home);
		else if (!command)
			chdir(home);
		free(home);
		g_sig.status = 0;
	}
	else
		home_not_set();
}

void	ft_cd(t_data *data, char **command)
{
	g_sig.status = 0;
	refresh_env(data->env, 1);
	if (!command[1] || command[1][0] == '\0')
	{
		ft_cd_home(data, command[1]);
		return ;
	}
	else if (command[2])
	{
		g_sig.status = 1;
		return (ft_putstr_fd("bash: cd: too many arguments\n", 2));
	}
	else if (!ft_strncmp(command[1], "~", 2))
		return (ft_cd_home(data, command[1]));
	else if (!ft_strncmp(command[1], "~/", 2))
		return (ft_cd_tild(data, command[1]));
	if (chdir(command[1]) != 0)
	{
		handle_error_cd(command[1], strerror(errno));
		g_sig.status = 1;
	}
}
