/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:51:54 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/10 17:10:13 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_env(t_cmd *cmd)
{
	if (cmd->words->type == WORD && cmd->words->next)
		cmd->words = cmd->words->next;
}