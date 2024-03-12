/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:48:07 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/11 18:01:08 by thomas           ###   ########.fr       */
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

void	execution(t_command *parsed_cmd, char **env)
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
}
