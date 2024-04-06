/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:19:26 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/06 23:26:12 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_cmd_scnd(t_cmd *cmd, t_command *command, t_cmd_word **zz,
		t_data *data)
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
		if (!data->tab_created && (*zz)->need_split == -1) // condition pour skip les $jdwdwqdwq en debut de commande mais pas pendant
		{
			if ((*zz)->next)
				(*zz) = (*zz)->next;
			return ;
		}
		else if (!data->tab_created)
		{
			parse_word((*zz), command->parsed_cmd);
			data->tab_created = 1;
		}
		skip_word((zz));
	}
}

void	parse_cmd(t_cmd *cmd, t_command *command, t_cmd_word **zz, t_data *data)
{
	parse_cmd_scnd(cmd, command, zz, data);
	if ((*zz)->type == ENV)
	{
		if ((*zz)->state == IN_QUOTE && (*zz)->next && (*zz)->next->state == 1)
			handle_no_expand(cmd->words, cmd->words->next);
		skip_env((*zz));
	}
	if (!is_redir((*zz)->type))
		(*zz) = (*zz)->next;
}

t_command	*parse(t_cmd *cmd, t_data *data)
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
			parse_cmd(cmd, command, &zz, data);
		tmp = ft_command_new();
		add_back_cmd_out(&command, tmp);
		command = command->next;
		i++;
		cmd = cmd->next;
		data->tab_created = 0;
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
	// print_list(data->lex);
	data->parsed_cmd = parse(data->cmd, data);
	// print_cmd_list(data->cmd);
	// print_parsed_cmd(data->parsed_cmd);
	return (0);
}
