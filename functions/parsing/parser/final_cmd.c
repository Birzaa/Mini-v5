/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:19:26 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/04 17:59:39 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_cmd_scnd(t_cmd *cmd, t_command *command, t_cmd_word **zz)
{
	if ((*zz)->type == REDIR_IN)
	{
		parse_r_in((*zz), &command->parsed_cmd->r_in, 0, cmd);
		skip_r_in((zz));
	}
	else if ((*zz)->type == HERE_DOC)
	{
		parse_r_in((*zz), &command->parsed_cmd->r_in, 1, cmd);
		skip_h_doc((zz));
	}
	else if ((*zz)->type == REDIR_OUT)
	{
		parse_r_out((*zz), &command->parsed_cmd->r_out, 0);
		skip_r_out((zz));
	}
	else if ((*zz)->type == DREDIR_OUT)
	{
		parse_r_out((*zz), &command->parsed_cmd->r_out, 1);
		skip_dr_out((zz));
	}
	else if ((*zz)->type == WORD)
	{
		parse_word((*zz), command->parsed_cmd);
		skip_word((zz));
	}
}

void	parse_cmd(t_cmd *cmd, t_command *command, t_cmd_word **zz)
{
	parse_cmd_scnd(cmd, command, zz);
	if ((*zz)->type == ENV)
	{
		if ((*zz)->state == IN_QUOTE && (*zz)->next && (*zz)->next->state == 1)
			handle_no_expand(cmd->words, cmd->words->next);
		skip_env((*zz));
	}
	if (!is_redir((*zz)->type))
		(*zz) = (*zz)->next;
}

t_command	*parse(t_cmd *cmd)
{
	t_command	*command;
	t_command	*head;
	t_command	*tmp;
	t_cmd_word	*zz;
	int			i;

	tmp = NULL;
	command = NULL;
	i = 0;
	command = init_command(command);
	if (!command)
		return (NULL);
	head = command;
	while (cmd)
	{
		command->parsed_cmd = init_redir(command->parsed_cmd);
		if (!command->parsed_cmd)
			return (NULL);
		zz = cmd->words;
		while (zz)
			parse_cmd(cmd, command, &zz);
		tmp = ft_command_new();
		add_back_cmd_out(&command, tmp);
		command = command->next;
		i++;
		cmd = cmd->next;
	}
	head->nb_command = i;
	return (head);
}

int	init_parse(t_data *data)
{
	parsing_status(data->lex);
	// print_list(data->lex);
	parse_space_in_quote(data->lex);
	index_quote(data->lex);
	data->cmd = parser(data->lex);
	parsing_expand(data->cmd, data);
	parsing_quote(data->cmd);
	data->parsed_cmd = parse(data->cmd);
	print_list(data->lex);
	// print_cmd_list(data->cmd);
	print_parsed_cmd(data->parsed_cmd);
	return (0);
}
