/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:21:52 by thomas            #+#    #+#             */
/*   Updated: 2024/04/11 04:13:30 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(char **command, t_data *data, t_pipex *p)
{
	if (ft_strcmp(command[0], "cd") == 0)
		ft_cd(data, command);
	else if (ft_strcmp(command[0], "pwd") == 0)
		ft_pwd(data);
	else if (ft_strcmp(command[0], "exit") == 0)
		ft_exit(data, p, command);
	else if (ft_strcmp(command[0], "export") == 0)
		ft_export(&data->env, p, command);
	else if (ft_strcmp(command[0], "env") == 0)
		ft_env(data, p, command);
	else if (ft_strcmp(command[0], "echo") == 0)
		ft_echo(command, p);
	else if (ft_strcmp(command[0], "unset") == 0)
		ft_unset(data->env, command);
}

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}
