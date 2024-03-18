/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:04:14 by thomas            #+#    #+#             */
/*   Updated: 2024/03/18 23:28:31 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *av, t_pipex *pipex)
{
	int		file;
	char	*buf;

	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
	{
		// MSG ERREUR
	}
	while (1)
	{
		write(1, "heredoc> ", 9);
		buf = get_next_line(0);
		if (!buf)
			exit(1);
		if (!ft_strcmp(av, buf))
			break ;
		write(file, buf, ft_strlen(buf));
		write(file, "\n", 1);
		free(buf);
	}
	free(buf);
	close(file);
	pipex->infile = open(".heredoc_tmp", O_RDONLY);
	if (pipex->infile < 0)
	{
		unlink(".heredoc_tmp");
		// MSG ERREUR
	}
}

void	open_redir_in(t_command *head, t_pipex *pipex)
{
	pipex->infile = pipex->saved_in;
	while (head->parsed_cmd->r_in)
	{
		if (!head->parsed_cmd->r_in->h_doc)
			pipex->infile = open(head->parsed_cmd->r_in->file, O_RDONLY, 0644);
		else
		{
			pipex->h_doc = 1;
			here_doc(head->parsed_cmd->r_in->file, pipex);
		}
		if (pipex->infile == -1)
		{
			printf("Impossible de in\n");
			exit(1);
		}
		head->parsed_cmd->r_in = head->parsed_cmd->r_in->next;
	}
}

void	open_redir_out(t_command *head, t_pipex *pipex)
{
	pipex->outfile = pipex->saved_out;
	while (head->parsed_cmd->r_out)
	{
		if (!head->parsed_cmd->r_out->append)
			pipex->outfile = open(head->parsed_cmd->r_out->file,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			pipex->outfile = open(head->parsed_cmd->r_out->file,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (pipex->outfile == -1)
		{
			printf("Impossible de out\n");
			exit(1);
		}
		head->parsed_cmd->r_out = head->parsed_cmd->r_out->next;
	}
}
