/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:04:14 by thomas            #+#    #+#             */
/*   Updated: 2024/04/10 13:13:59 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*here_doc(char *av, t_pipex *pipex, int index, t_data *data)
{
	int		file;
	char	*dest_file;

	dest_file = create_dest_file(pipex, index, av);
	file = open(dest_file, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
	{
		free(pipex->h_doc_name[index]);
		return (NULL);
	}
	signal(SIGINT, &exec_here_doc);
	if (g_sig.status == 130)
		g_sig.status = 0;
	if (!reading_hdoc(file, pipex, data, av))
	{
		free(dest_file);
		return (NULL);
	}
	close(file);
	free(dest_file);
	return (pipex->h_doc_name[index]);
}

void	open_redir_in(t_command *head, t_pipex *pipex)
{
	t_redir_in_2	*tmp;

	pipex->infile = pipex->saved_in;
	tmp = head->parsed_cmd->r_in;
	while (tmp)
	{
		if (!tmp->h_doc)
			pipex->infile = open(tmp->file, O_RDONLY, 0644);
		else
		{
			pipex->h_doc = 1;
			if (tmp->file)
				pipex->infile = open(tmp->file, O_RDONLY, 0644);
		}
		if (pipex->infile == -1)
		{
			g_sig.status = 1;
			handle_error(tmp->file, strerror(errno));
			return ;
		}
		tmp = tmp->next;
	}
}

void	open_redir_out(t_command *head, t_pipex *pipex)
{
	t_redir_out	*tmp;

	tmp = head->parsed_cmd->r_out;
	pipex->outfile = pipex->saved_out;
	while (tmp)
	{
		if (!tmp->append)
			pipex->outfile = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		else
			pipex->outfile = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		if (pipex->outfile == -1)
		{
			g_sig.status = 1;
			handle_error(tmp->file, strerror(errno));
			return ;
		}
		tmp = tmp->next;
	}
}

void	create_h_doc(t_command *parsed_cmd, t_pipex *pipex, t_data *data)
{
	t_command		*current_cmd;
	t_redir_in_2	*r_in;
	int				index;

	index = 0;
	current_cmd = parsed_cmd;
	while (pipex->idx < pipex->nb_cmd)
	{
		if (current_cmd->parsed_cmd->r_in)
		{
			r_in = current_cmd->parsed_cmd->r_in;
			while (r_in)
			{
				if (r_in->h_doc)
				{
					r_in->file = here_doc(r_in->file, pipex, index++, data);
					if (!r_in->file)
						return ;
				}
				r_in = r_in->next;
			}
		}
		pipex->idx++;
		current_cmd = current_cmd->next;
	}
}
