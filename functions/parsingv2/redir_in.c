/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:26:51 by thomas            #+#    #+#             */
/*   Updated: 2024/03/05 19:00:21 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_r_in(t_cmd_word *cmd)
{
	t_redir_in_2	*r_in;

	r_in = malloc(sizeof(t_redir_in_2));
	if (!r_in)
		return ;
	while (cmd->type == WHITE_SPACE)
		cmd = cmd->next;
	if (cmd->type == WORD)
	{
		r_in->file = cmd->content;
		r_in->h_doc = 0;
		r_in->next = NULL;
		cmd = cmd->next;
	}
}
