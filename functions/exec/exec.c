/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:48:07 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/04 18:57:41 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_pipex *pipex);

void	close_h_doc(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->h_doc)
	{
		while (pipex->h_doc_name[i])
		{
			unlink(pipex->h_doc_name[i]);
			if (pipex->need_free)
			{
				free(pipex->h_doc_name[i]);
			}
			i++;
		}
		free(pipex->h_doc_name);
	}
}

void	parent_free(t_pipex *pipex)
{
	close(pipex->infile);
	close(pipex->outfile);
	free(pipex->pipe);
}

void	open_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nb_cmd - 1)
	{
		if (pipe(pipex->pipe + 2 * i) < 0)
		{
			parent_free(pipex);
		}
		i++;
	}
}

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < (2 * (pipex->nb_cmd - 1)))
	{
		close(pipex->pipe[i]);
		i++;
	}
}

void	child(t_pipex p, char **cmd, char **env, t_data *data)
{
	g_sig.pid = 0;
	p.pid = fork();
	if (p.pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (p.pid == 0)
	{
		if (p.idx == 0)
		{
			// Redirection de l'entrée standard pour le premier processus
			dup2(p.infile, STDIN_FILENO);
			close(p.infile);
		}
		else
		{
			// Redirection de l'entrée standard depuis le tuyau précédent
			if (p.infile != p.saved_in)
			{
				dup2(p.infile, STDIN_FILENO);
				close(p.infile);
			}
			else
			{
				dup2(p.pipe[2 * (p.idx - 1)], STDIN_FILENO);
				close(p.pipe[2 * (p.idx - 1)]);
			}
		}
		if (p.idx == p.nb_cmd - 1)
		{
			// Redirection de la sortie standard pour le dernier processus
			dup2(p.outfile, STDOUT_FILENO);
			close(p.outfile);
		}
		else
		{
			// Redirection de la sortie standard vers le tuyau actuel
			if (p.outfile != p.saved_out)
			{
				dup2(p.outfile, STDOUT_FILENO);
				close(p.outfile);
			}
			else
			{
				dup2(p.pipe[2 * p.idx + 1], STDOUT_FILENO);
				close(p.pipe[2 * p.idx + 1]);
			}
		}
		// Fermeture de tous les descripteurs de fichiers des tuyaux dans le processus enfant
		close_pipes(&p);
		if (!is_builtin(cmd[0]) && cmd)
			execute_cmd(env, cmd, data, &p);
		else
		{
			execute_builtin(cmd, data, &p);
			free_lexer(data->lex);
			free_parser(data->cmd, data->parsed_cmd);
			free_env(data->env);
			ft_free_tab(data->envp);
			parent_free(&p);
			exit(0);
		}
	}
}

void	execution(t_command *parsed_cmd, char **env, t_data *data)
{
	t_pipex		pipex;
	t_command	*current_cmd;
	int			status;

	pipex.pipe = NULL;
	current_cmd = parsed_cmd;
	pipex.need_exec = 0;
	pipex.need_free = 0;
	pipex.nb_cmd = parsed_cmd->nb_command;
	pipex.saved_in = dup(STDIN_FILENO);
	pipex.h_doc = 0;
	pipex.idx = 0;
	pipex.saved_out = dup(STDOUT_FILENO);
	nb_h_doc(current_cmd, &pipex);
	create_h_doc(current_cmd, &pipex, current_cmd->parsed_cmd->full_cmd, data);
	if(g_sig.status == 130)
		caca(current_cmd, &pipex, current_cmd->parsed_cmd->full_cmd, data);
	if (current_cmd->parsed_cmd->full_cmd && pipex.nb_cmd == 1
		&& is_builtin(current_cmd->parsed_cmd->full_cmd[0]))
	{
		pipex.fd_echo = 1;
		open_redir_in(current_cmd, &pipex);
		open_redir_out(current_cmd, &pipex);
		execute_builtin(current_cmd->parsed_cmd->full_cmd, data, &pipex);
	}
	else if (current_cmd->parsed_cmd->full_cmd && !pipex.need_exec
		&& ft_getenv_check_tab(data->envp, "PATH="))
	{
		pipex.pipe = (int *)malloc((sizeof(int) * (2 * (pipex.nb_cmd - 1))));
		if (!pipex.pipe)
			return ;
		open_pipes(&pipex);
		while (pipex.idx < pipex.nb_cmd)
		{
			g_sig.status = 0;
			pipex.fd_echo = 0;
			open_redir_in(current_cmd, &pipex);
			open_redir_out(current_cmd, &pipex);
			if(g_sig.status != 1)
				child(pipex, current_cmd->parsed_cmd->full_cmd, env, data);
			pipex.idx++;
			current_cmd = current_cmd->next;
		}
		close_pipes(&pipex);
		parent_free(&pipex);
		while (pipex.idx)
		{
			waitpid(-1, &status, 0);
			if (WIFEXITED(status))
				g_sig.status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				break ;
			else
				g_sig.status = 127;
			pipex.idx--;
		}
	}
	else if (current_cmd->parsed_cmd->r_in)
	{
		open_redir_in(current_cmd, &pipex);
	}
	else if (current_cmd->parsed_cmd->r_out)
	{
		open_redir_out(current_cmd, &pipex);
	}
	close_h_doc(&pipex);
}
