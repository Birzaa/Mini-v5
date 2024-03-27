/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:51:54 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/27 15:32:17 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_env(t_cmd_word *cmd)
{
	if (cmd->type == WORD && cmd->next)
		cmd = cmd->next;
}
