/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_doc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:30:06 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/10 09:24:32 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	while_h_r_in(t_redir_in_2 *r_in, int index)
{
	while (r_in)
	{
		if (r_in->h_doc)
		{
			r_in->file = NULL;
			index++;
		}
		r_in = r_in->next;
	}
	return (index);
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
