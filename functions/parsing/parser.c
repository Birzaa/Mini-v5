/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:55:20 by thenwood          #+#    #+#             */
/*   Updated: 2024/02/22 17:41:51 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_stack *lst)
{
	t_cmd	*cmd;
	int		i;

	cmd = malloc(sizeof(t_cmd));
	cmd->node = lst->head;
	i = 0;
	while (i < lst->size)
	{
		cmd->cmd = ft_strjoin(cmd->node->content, " ");
		printf("%s\n", cmd->cmd);
		if (cmd->node->type == PIPE_LINE)
		{
			cmd = cmd->next;
		}
		cmd->node = cmd->node->next;
		i++;
	}
}
