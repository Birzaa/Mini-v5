/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:23:48 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/07 19:25:13 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir_out(t_redir_out *redir_out)
{
	t_redir_out	*tmp;

	if (!redir_out)
		return ;
	while (redir_out)
	{
		tmp = redir_out;
		redir_out = redir_out->next;
		free(tmp->file);
		free(tmp);
	}
}

void	free_redir_in_2(t_redir_in_2 *redir_in_2)
{
	t_redir_in_2	*tmp;

	if (!redir_in_2)
		return ;
	while (redir_in_2)
	{
		tmp = redir_in_2;
		redir_in_2 = redir_in_2->next;
		free(tmp->file);
		free(tmp);
	}
}

void	free_parsed_cmd(t_parsed_cmd *parsed_cmd)
{
	if (!parsed_cmd)
		return ;
	free(parsed_cmd->full_cmd);
	free_redir_in_2(parsed_cmd->r_in);
	free_redir_out(parsed_cmd->r_out);
	free(parsed_cmd);
}

void	free_command(t_command *command)
{
	t_command	*tmp;

	if (!command)
		return ;
	while (command)
	{
		tmp = command;
		command = command->next;
		free_parsed_cmd(tmp->parsed_cmd);
		free(tmp);
	}
}

void	free_parser(t_command *head)
{
	free_command(head);
}
