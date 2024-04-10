/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_doc_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:58:10 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/10 12:41:06 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_pipe_h_doc(t_command *parsed_cmd, t_pipex *pipex)
{
	t_command		*current_cmd;
	t_redir_in_2	*r_in;
	int				i;
	int				count;

	count = 0;
	i = 0;
	current_cmd = parsed_cmd;
	while (current_cmd && i < pipex->nb_cmd)
	{
		if (i > 0)
		{
			r_in = current_cmd->parsed_cmd->r_in;
			while (r_in)
			{
				if (r_in->h_doc)
					count++;
				r_in = r_in->next;
			}
		}
		i++;
		current_cmd = current_cmd->next;
	}
	if (count > 0)
		pipex->jss_a_terre = 1;
}

void	caca(t_command *parsed_cmd, t_pipex *pipex, char **tab, t_data *data)
{
	t_command		*current_cmd;
	t_redir_in_2	*r_in;
	int				index;

	(void)tab;
	(void)data;
	index = 0;
	current_cmd = parsed_cmd;
	while (pipex->idx < pipex->nb_cmd)
	{
		if (current_cmd->parsed_cmd->r_in)
		{
			r_in = current_cmd->parsed_cmd->r_in;
			index += while_h_r_in(r_in, index);
		}
		pipex->idx++;
		current_cmd = current_cmd->next;
	}
	pipex->idx = 0;
}

void	nb_doc_bis(t_pipex *pipex)
{
	pipex->h_doc = 1;
	pipex->h_doc_name = calloc(pipex->nb_h_doc + 1, sizeof(char *));
	if (!pipex->h_doc_name)
		return ;
	pipex->h_doc_name[pipex->nb_h_doc++] = NULL;
}

void	nb_h_doc(t_command *parsed_cmd, t_pipex *pipex)
{
	t_command		*current_cmd;
	t_redir_in_2	*r_in;

	pipex->nb_h_doc = 0;
	current_cmd = parsed_cmd;
	while (pipex->idx < pipex->nb_cmd)
	{
		if (current_cmd->parsed_cmd->r_in)
		{
			r_in = current_cmd->parsed_cmd->r_in;
			while (r_in)
			{
				if (r_in->h_doc)
					pipex->nb_h_doc++;
				r_in = r_in->next;
			}
		}
		pipex->idx++;
		current_cmd = current_cmd->next;
	}
	if (pipex->nb_h_doc)
	{
		nb_doc_bis(pipex);
	}
}
