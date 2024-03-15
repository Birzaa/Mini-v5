/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:21:52 by thomas            #+#    #+#             */
/*   Updated: 2024/03/15 15:13:30 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	execute_builtin(t_cmd *cmd, char **command, t_data *data)
{
	if (ft_strcmp(command[0], "cd") == 0)
		ft_cd(command[1], data);
	else if (ft_strcmp(command[0], "pwd") == 0)
		ft_pwd(cmd);
	else if (ft_strcmp(command[0], "cd") == 0)
		ft_cd(command[1], data);
	else if (ft_strcmp(command[0], "export") == 0)
	{
		if (!command[1])
			return (export_no_arg(data->env));
		export(&data->env, command[1]);
	}
	else if (ft_strcmp(command[0], "env") == 0)
		print_env(data->env);
	else if (ft_strcmp(command[0], "echo") == 0)
		ft_echo(command);
	else if (ft_strcmp(command[0], "unset") == 0)
	{
		if (!command[1])
			return ;
		unset(data->env, command[1]);
	}
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
} */