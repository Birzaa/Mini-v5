/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:48:07 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/10 12:37:51 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipex(t_pipex *pipex, t_command *parsed_cmd, t_data *data,
		t_command *current_cmd)
{
	pipex->pipe = NULL;
	pipex->need_exec = 0;
	pipex->need_free = 0;
	pipex->jss_a_terre = 0;
	pipex->nb_cmd = parsed_cmd->nb_command;
	cmd_pipe_h_doc(parsed_cmd, pipex);
	pipex->saved_in = dup(STDIN_FILENO);
	pipex->h_doc = 0;
	pipex->idx = 0;
	pipex->saved_out = dup(STDOUT_FILENO);
	nb_h_doc(current_cmd, pipex);
	pipex->idx = 0;
	create_h_doc(current_cmd, pipex, data);
	if (g_sig.status == 130)
		caca(current_cmd, pipex, current_cmd->parsed_cmd->full_cmd, data);
	pipex->idx = 0;
}

void	exec_bultins(t_pipex *pipex, t_data *data, t_command *current_cmd)
{
	pipex->fd_echo = 1;
	open_redir_in(current_cmd, pipex);
	open_redir_out(current_cmd, pipex);
	execute_builtin(current_cmd->parsed_cmd->full_cmd, data, pipex);
}

void	exec_cmd_pipe(t_pipex *pipex, t_data *data, t_command *current_cmd,
		char **env)
{
	pipex->pipe = (int *)malloc((sizeof(int) * (2 * (pipex->nb_cmd - 1))));
	if (!pipex->pipe)
		return ;
	open_pipes(pipex);
	while (pipex->idx < pipex->nb_cmd)
	{
		g_sig.status = 0;
		pipex->fd_echo = 0;
		open_redir_in(current_cmd, pipex);
		open_redir_out(current_cmd, pipex);
		if (current_cmd->parsed_cmd->nb_cmd)
		{
			if (g_sig.status != 1)
				child(*pipex, current_cmd->parsed_cmd->full_cmd, env, data);
		}
		pipex->idx++;
		current_cmd = current_cmd->next;
	}
	close_pipes(pipex);
	parent_free(pipex);
}

void	wait_child(t_pipex *pipex)
{
	int	status;

	status = 1;
	while (pipex->idx)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			g_sig.status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			break ;
		else
			g_sig.status = 127;
		pipex->idx--;
	}
}

void	execution(t_command *parsed_cmd, char **env, t_data *data)
{
	t_pipex		pipex;
	t_command	*current_cmd;

	current_cmd = parsed_cmd;
	init_pipex(&pipex, parsed_cmd, data, current_cmd);
	if (current_cmd->parsed_cmd->full_cmd && pipex.nb_cmd == 1
		&& is_builtin(current_cmd->parsed_cmd->full_cmd[0]))
		exec_bultins(&pipex, data, current_cmd);
	else if ((current_cmd->parsed_cmd->full_cmd || pipex.jss_a_terre
			|| pipex.nb_cmd > 1) && !pipex.need_exec
		&& ft_getenv_check_tab(data->envp, "PATH="))
	{
		exec_cmd_pipe(&pipex, data, current_cmd, env);
		wait_child(&pipex);
	}
	else if (current_cmd->parsed_cmd->r_in)
		open_redir_in(current_cmd, &pipex);
	else if (current_cmd->parsed_cmd->r_out)
		open_redir_out(current_cmd, &pipex);
	close_h_doc(&pipex);
}
