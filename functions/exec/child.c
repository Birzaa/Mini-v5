/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:42:05 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/14 14:11:41 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(char **cmd, char **env, t_data *data, t_pipex *p)
{
	if (!is_builtin(cmd[0]) && cmd)
	{
		close(p->saved_in);
		close(p->saved_out);
		execute_cmd(env, cmd, data, p);
	}
	else
	{
		close(p->saved_in);
		close(p->saved_out);
		execute_builtin(cmd, data, p);
		free_lexer(data->lex);
		free_parser(data->cmd, data->parsed_cmd);
		free_env(data->env);
		ft_free_tab(data->envp);
		parent_free(p);
		if (p->nb_h_doc)
			free(p->h_doc_name);
		exit(0);
	}
}

void	dup_fd_child(t_pipex *p)
{
	if (p->idx == 0)
	{
		dup2(p->infile, STDIN_FILENO);
		close(p->infile);
	}
	else
	{
		if (p->infile != p->saved_in)
		{
			dup2(p->infile, STDIN_FILENO);
			close(p->infile);
		}
		else
		{
			dup2(p->pipe[2 * (p->idx - 1)], STDIN_FILENO);
			close(p->pipe[2 * (p->idx - 1)]);
		}
	}
}

void	dup_fd_child_bis(t_pipex *p)
{
	if (p->idx == p->nb_cmd - 1)
	{
		dup2(p->outfile, STDOUT_FILENO);
		close(p->outfile);
	}
	else
	{
		if (p->outfile != p->saved_out)
		{
			dup2(p->outfile, STDOUT_FILENO);
			close(p->outfile);
		}
		else
		{
			dup2(p->pipe[2 * p->idx + 1], STDOUT_FILENO);
			close(p->pipe[2 * p->idx + 1]);
		}
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
		dup_fd_child(&p);
		dup_fd_child_bis(&p);
		close_pipes(&p);
		exec_child(cmd, env, data, &p);
	}
}
