/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:19:26 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/10 18:00:49 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_cmd_scnd(t_cmd *cmd, t_command *command)
{
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
}

void	parse_cmd(t_cmd *cmd, t_command *command)
{
	parse_cmd_scnd(cmd, command);
	if (cmd->words->type == WORD)
	{
		parse_word(cmd->words, command->parsed_cmd);
		skip_word(cmd);
	}
	else if (cmd->words->type == ENV)
	{
		if (cmd->words->state == IN_QUOTE && cmd->words->next
			&& cmd->words->next->state == 1)
			handle_no_expand(cmd->words, cmd->words->next);
		skip_env(cmd);
	}
	if (!is_redir(cmd->words->type))
		cmd->words = cmd->words->next;
}

t_command	*parse(t_cmd *cmd)
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
			parse_cmd(cmd, command);
		tmp = ft_command_new();
		add_back_cmd_out(&command, tmp);
		command = command->next;
		i++;
		cmd = cmd->next;
	}
	head->nb_command = i;
	return (head);
}

void	init_parse(t_data *data)
{
	data->cmd = parser(data->lex);
	test_exp(data->cmd, data);
	parsing_quote(data->cmd);
	data->parsed_cmd = parse(data->cmd);
	// print_cmd_list(data->cmd);
	print_parsed_cmd(data->parsed_cmd);
}
