/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:48:07 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/18 17:02:59 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_free(t_pipex *pipex)
{
	close(pipex->infile);
	close(pipex->outfile);
	/* if (pipex->here_doc)
		unlink(".heredoc_tmp"); */
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

void	child(t_pipex p, char **cmd, char **env)
{
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
			close(p.infile); // Fermeture du descripteur d'entrée inutilisé
		}
		else
		{
			// Redirection de l'entrée standard depuis le tuyau précédent
			dup2(p.pipe[0], STDIN_FILENO);
			close(p.pipe[0]); // Fermeture du descripteur de lecture inutilisé
		}
		if (p.idx == p.nb_cmd - 1)
		{
			// Redirection de la sortie standard pour le dernier processus
			dup2(p.outfile, STDOUT_FILENO);
			close(p.outfile); // Fermeture du descripteur de sortie inutilisé
		}
		else
		{
			// Redirection de la sortie standard vers le tuyau suivant
			dup2(p.pipe[1], STDOUT_FILENO);
			close(p.pipe[1]); // Fermeture du descripteur d'écriture inutilisé
		}
		// Fermeture de tous les autres descripteurs de fichiers du tuyau dans le processus enfant
		close(p.pipe[0]);
		close(p.pipe[1]);
		close(p.infile);
		close(p.outfile);
		execute_cmd(env, cmd);
	}
}

void	execution(t_command *parsed_cmd, char **env)
{
	t_pipex		pipex;
	t_command	*current_cmd;

	pipex.nb_cmd = parsed_cmd->nb_command;
	pipex.saved_in = dup(STDIN_FILENO);
	pipex.saved_out = dup(STDOUT_FILENO);
	pipex.pipe = (int *)malloc((sizeof(int) * (2 * (pipex.nb_cmd - 1))));
	if (!pipex.pipe)
		printf("FLOP"); // modif
	open_pipes(&pipex);
	pipex.idx = 0;
	current_cmd = parsed_cmd;
	while (pipex.idx < pipex.nb_cmd)
	{
		open_redir_in(current_cmd, &pipex);
		open_redir_out(current_cmd, &pipex);
		child(pipex, current_cmd->parsed_cmd->full_cmd, env);
		pipex.idx++;
		current_cmd = current_cmd->next;
	}
	close_pipes(&pipex);
	waitpid(-1, NULL, 0);
	parent_free(&pipex);
}
