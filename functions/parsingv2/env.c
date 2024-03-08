/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:51:54 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/08 18:57:51 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_env(t_cmd *cmd)
{	
	

	if (cmd->words->type == WORD && cmd->words->next)
		cmd->words = cmd->words->next;
}

// '"$HOME"'