/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:01:09 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/09 23:44:02 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_dr_out(t_cmd *cmd)
{
	if (cmd->words->type == DREDIR_OUT && cmd->words->next)
		cmd->words = cmd->words->next;
	while (cmd->words->type == WHITE_SPACE && cmd->words->next)
		cmd->words = cmd->words->next;
	if (cmd->words->type == WORD && cmd->words->next)
		cmd->words = cmd->words->next;
}

void	skip_r_out(t_cmd *cmd)
{
	if (cmd->words->type == REDIR_OUT && cmd->words->next)
		cmd->words = cmd->words->next;
	while (cmd->words->type == WHITE_SPACE && cmd->words->next)
		cmd->words = cmd->words->next;
	if (cmd->words->type == WORD && cmd->words->next)
		cmd->words = cmd->words->next;
}

void	skip_h_doc(t_cmd *cmd)
{
	if (cmd->words->type == HERE_DOC && cmd->words->next)
		cmd->words = cmd->words->next;
	while (cmd->words->type == WHITE_SPACE && cmd->words->next)
		cmd->words = cmd->words->next;
	if (cmd->words->type == WORD && cmd->words->next)
		cmd->words = cmd->words->next;
}

void	skip_r_in(t_cmd *cmd)
{
	if (cmd->words->type == REDIR_IN && cmd->words->next)
		cmd->words = cmd->words->next;
	while (cmd->words->type == WHITE_SPACE && cmd->words->next)
		cmd->words = cmd->words->next;
	if (cmd->words->type == WORD && cmd->words->next)
		cmd->words = cmd->words->next;
}

void	skip_word(t_cmd *cmd)
{
	enum e_state	state;

	state = cmd->words->state;
	if (cmd->words->type == WORD && cmd->words->next)
		cmd->words = cmd->words->next;
	while (cmd->words)
	{
		if ((cmd->words->type == WHITE_SPACE || cmd->words->type == WORD
				|| cmd->words->type == DOUBLE_QUOTE || cmd->words->type == QOUTE
				|| cmd->words->state == state) && cmd->words->next)
			cmd->words = cmd->words->next;
		else
			break ;
	}
	if(cmd->words)
		printf("apres skip word : '%s'\n", cmd->words->content);
}
