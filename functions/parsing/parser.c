/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:55:20 by thenwood          #+#    #+#             */
/*   Updated: 2024/02/22 22:31:08 by abougrai         ###   ########.fr       */
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
	while (i < lst->size && cmd->node)
	{
		//cmd->cmd = ft_strjoin(cmd->node->content, " ");
		if (cmd->node->type == PIPE_LINE)
		{
			cmd = cmd->next;
		}
		cmd->node = cmd->node->next;
		i++;
	}
}
