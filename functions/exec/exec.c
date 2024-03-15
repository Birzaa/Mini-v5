/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:48:07 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/15 16:00:48 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipex(char **cmd, char **env)
{
	pid_t	pid;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
	{
		printf("FLOP\n");
		exit(0);
		// ERREUR
	}
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], STDOUT_FILENO);
		execute_cmd(env, cmd);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], STDIN_FILENO);
	}
}

void	execution(t_command *parsed_cmd, char **env)
{
	int	i;

	int	fd_in;
	int	fd_out;
	(void)env;
	(void)i;
	i = 0;
	fd_in = open_redir_in2(parsed_cmd);
	fd_out = open_redir_out(parsed_cmd);
	dup2(fd_in, 0);
	while (i < parsed_cmd->nb_command-1)
	{		
		pipex(parsed_cmd->parsed_cmd->full_cmd, env);
		i++;
		parsed_cmd = parsed_cmd->next;
	}
	dup2(fd_out, 1);
}
