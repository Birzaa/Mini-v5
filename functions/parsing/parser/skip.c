/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:01:09 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/10 08:54:15 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_dr_out(t_cmd_word **cmd)
{
	if ((*cmd)->type == DREDIR_OUT && (*cmd)->next)
		(*cmd) = (*cmd)->next;
	while ((*cmd)->type == WHITE_SPACE && (*cmd)->next)
		(*cmd) = (*cmd)->next;
	if ((*cmd)->type == WORD && (*cmd)->next)
		(*cmd) = (*cmd)->next;
}

void	skip_r_out(t_cmd_word **cmd)
{
	if ((*cmd)->type == REDIR_OUT && (*cmd)->next)
		(*cmd) = (*cmd)->next;
	while ((*cmd)->type == WHITE_SPACE && (*cmd)->next)
		(*cmd) = (*cmd)->next;
	if ((*cmd)->type == WORD && (*cmd)->next)
		(*cmd) = (*cmd)->next;
}

void	skip_h_doc(t_cmd_word **cmd)
{
	if ((*cmd)->type == HERE_DOC && (*cmd)->next)
		(*cmd) = (*cmd)->next;
	while ((*cmd)->type == WHITE_SPACE && (*cmd)->next)
		(*cmd) = (*cmd)->next;
	if ((*cmd)->type == WORD && (*cmd)->next)
		(*cmd) = (*cmd)->next;
}

void	skip_r_in(t_cmd_word **cmd)
{
	if ((*cmd)->type == REDIR_IN && (*cmd)->next)
		(*cmd) = (*cmd)->next;
	while ((*cmd)->type == WHITE_SPACE && (*cmd)->next)
		(*cmd) = (*cmd)->next;
	if ((*cmd)->type == WORD && (*cmd)->next)
		(*cmd) = (*cmd)->next;
}

void	skip_word(t_cmd_word **cmd)
{
	if ((*cmd)->type == WORD && (*cmd)->next)
		(*cmd) = (*cmd)->next;
	while (cmd)
	{
		if (((*cmd)->type == WHITE_SPACE || (*cmd)->type == WORD)
			&& (*cmd)->next)
			(*cmd) = (*cmd)->next;
		else
			break ;
	}
}
