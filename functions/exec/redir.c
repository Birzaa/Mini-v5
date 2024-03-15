/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:04:14 by thomas            #+#    #+#             */
/*   Updated: 2024/03/15 18:24:02 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redir_in2(t_command *head)
{
	int	fd;

	fd = STDIN_FILENO;
	while (head->parsed_cmd->r_in)
	{
		if (!head->parsed_cmd->r_in->h_doc)
			fd = open(head->parsed_cmd->r_in->file, O_RDONLY, 0644);
		if (fd == -1)
		{
			printf("Impossible de in\n");
			exit(1);
			// ERREUR
		}
		head->parsed_cmd->r_in = head->parsed_cmd->r_in->next;
	}
	return (fd);
}

int	open_redir_out(t_command *head)
{
	int	fd;

	fd = STDOUT_FILENO;
	while (head->parsed_cmd->r_out)
	{
		if (!head->parsed_cmd->r_out->append)
			fd = open(head->parsed_cmd->r_out->file,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(head->parsed_cmd->r_out->file,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			printf("Impossible de out\n");
			exit(1);
			// ERREUR
		}
		head->parsed_cmd->r_out = head->parsed_cmd->r_out->next;
	}
	return (fd);
}
