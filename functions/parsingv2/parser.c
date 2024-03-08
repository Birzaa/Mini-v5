/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:19:26 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/08 19:02:28 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*init_command(t_command *list)
{
	list = ft_calloc(sizeof(t_command), 1);
	if (!list)
		return (NULL);
	list->nb_command = 0;
	list->parsed_cmd = NULL;
	list->next = NULL;
	return (list);
}

t_parsed_cmd	*init_redir(t_parsed_cmd *list)
{
	list = ft_calloc(sizeof(t_parsed_cmd), 1);
	if (!list)
		return (NULL);
	list->r_in = NULL;
	list->r_out = NULL;
	list->full_cmd = NULL;
	return (list);
}

void	parse_cmd(t_cmd *cmd, t_command *command, t_data *data)
{
	(void)data;
	if (cmd->words->type == REDIR_IN)
		parse_r_in(cmd->words, &command->parsed_cmd->r_in, 0, cmd);
	else if (cmd->words->type == HERE_DOC)
	{
		parse_r_in(cmd->words, &command->parsed_cmd->r_in, 1, cmd);
		skip_h_doc(cmd);
	}
	else if (cmd->words->type == REDIR_OUT)
	{
		parse_r_out(cmd->words, &command->parsed_cmd->r_out, 0);
		skip_r_out(cmd);
	}
	else if (cmd->words->type == DREDIR_OUT)
	{
		parse_r_out(cmd->words, &command->parsed_cmd->r_out, 1);
		skip_dr_out(cmd);
	}
	else if (cmd->words->type == WORD)
	{
		parse_word(cmd->words, command->parsed_cmd);
		skip_word(cmd);
	}
	else if (cmd->words->type == ENV)
	{
		// change content $ = $ content
		// del
		//
		skip_env(cmd);
	}
	if (!is_redir(cmd->words->type))
		cmd->words = cmd->words->next;
}

t_command	*parse(t_cmd *cmd, t_data *data)
{
	t_command	*command;
	t_command	*head;
	t_command	*tmp;
	int			i;

	tmp = NULL;
	command = NULL;
	i = 0;
	command = init_command(command);
	head = command;
	while (cmd)
	{
		command->parsed_cmd = init_redir(command->parsed_cmd);
		if (!command)
			return (NULL);
		while (cmd->words)
			parse_cmd(cmd, command, data);
		tmp = ft_command_new();
		add_back_cmd_out(&command, tmp);
		command = command->next;
		i++;
		cmd = cmd->next;
	}
	head->nb_command = i;
	return (head);
}

