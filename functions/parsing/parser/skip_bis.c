/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:00:26 by thomas            #+#    #+#             */
/*   Updated: 2024/04/06 12:02:47 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip(t_cmd_word *cmd)
{
	if (cmd->type == DREDIR_OUT && cmd->next)
		cmd = cmd->next;
	while (cmd->type == WHITE_SPACE && cmd->next)
		cmd = cmd->next;
	if (cmd->type == WORD && cmd->next)
		cmd = cmd->next;
}