/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:43:53 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/12 13:46:56 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
