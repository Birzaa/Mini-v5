/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:04:14 by thomas            #+#    #+#             */
/*   Updated: 2024/03/18 15:00:32 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_redir_in(t_command *head, t_pipex *pipex)
{
	pipex->infile = pipex->saved_in;
	while (head->parsed_cmd->r_in)
	{
		if (!head->parsed_cmd->r_in->h_doc)
			pipex->infile = open(head->parsed_cmd->r_in->file, O_RDONLY, 0644);
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
