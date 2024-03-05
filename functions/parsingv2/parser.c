/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:19:26 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/05 17:16:11 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	ETAPES :
	1) Esquiver espaces
	2) Si cest une reddirection => parse redir
	3) Si cest un mot suivit ou non dun flag => parse cmd
	4) Voir si ya une redirection out => redir out
	5) Si on rencontre un | nvlle commande
 */

void	parse(t_data *data)
{
	t_command	*command;
	t_stack		*cmd;
	
	cmd = data->lex->head;
	while (cmd->head)
	{
		if (cmd->head->type == PIPE_LINE)
			command = command->next;
		while (cmd->head->type == WHITE_SPACE)
			cmd->head = cmd->head->next;
		if (cmd->head->type == REDIR_IN)
			//PARSE REDIR in
		else if (cmd->head->type == HERE_DOC)
			//PARSE h_doc
		else if (cmd->head->type == WORD)
			// PARSE CMD
		else if (cmd->head->type == REDIR_IN)
			//PARSE R_out
		else if (cmd->head->type == DREDIR_OUT)
			//Parse D_r_out
	}
}
