/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:48:07 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/15 14:31:08 by abougrai         ###   ########.fr       */
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


void	pipex(char **cmd, char **env)
{
	pid_t	pid;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
	{
		printf("FLOP\n");
		// ERREUR
	}
	pid = fork();
	if (!pid)
	{
		dup2(p_fd[1], 1);
		close(p_fd[0]);
		execute_cmd(env, cmd);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
	}
}

/* void	execution(t_command *parsed_cmd, char **env)
{
	int	fd_in;
	int	fd_out;
	int	i;

	(void)env;
	(void)i;
	i = 0;
	fd_in = open_redir_in2(parsed_cmd);
	fd_out = open_redir_out(parsed_cmd);
	while (i < parsed_cmd->nb_command)
	{
		pipex(parsed_cmd->parsed_cmd->full_cmd, env);
		i++;
		parsed_cmd = parsed_cmd->next;
	}
	dup2(fd_out, STDOUT_FILENO);
} */
