/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_doc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:30:06 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/04 17:57:29 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	caca(t_command *parsed_cmd, t_pipex *pipex, char **tab,
		t_data *data)
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
					r_in->file = NULL;
					index++;
				}
				r_in = r_in->next;
			}
		}
		pipex->idx++;
		current_cmd = current_cmd->next;
	}
	pipex->idx = 0;
	(void)tab;
	(void)data;
}