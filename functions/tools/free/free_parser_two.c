/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 15:23:04 by thomas            #+#    #+#             */
/*   Updated: 2024/03/24 19:13:41 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir_out(t_redir_out *r_out)
{
	t_redir_out	*next_out;

	while (r_out)
	{
		next_out = r_out->next;
		free(r_out->file);
		free(r_out);
		r_out = next_out;
	}
}

void	free_redir_in_2(t_redir_in_2 *r_in)
{
	t_redir_in_2	*next_in;

	while (r_in)
	{
		next_in = r_in->next;
		free(r_in->file);
		free(r_in);
		r_in = next_in;
	}
}

void	free_parsed_cmd(t_parsed_cmd *parsed_cmd)
{
	if (parsed_cmd)
	{
		// ft_free_tab(parsed_cmd->full_cmd);
		/* free_redir_out(parsed_cmd->r_out);
		free_redir_in_2(parsed_cmd->r_in);
		free(parsed_cmd); */
	}
}

void	free_command(t_command *command)
{
	t_command	*next_command;

	while (command)
	{
		next_command = command->next;
		free_parsed_cmd(command->parsed_cmd);
		free(command);
		command = next_command;
	}
}
