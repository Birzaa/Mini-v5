/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:55:20 by thenwood          #+#    #+#             */
/*   Updated: 2024/02/23 16:16:54 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list2(t_cmd *cmd)
{
	t_cmd	*temp;

	temp = cmd;
	while (cmd)
	{
		printf("%s", temp->cmd);
		temp = temp->next;
	}
}

void	parser(t_stack *lst)
{
	t_cmd	*cmd;
	int		i;
	t_cmd	*next_cmd;
	t_cmd	*head;

	cmd = malloc(sizeof(t_cmd));
	cmd->node = lst->head;
	cmd->next = NULL;
	head = cmd;
	i = 0;
	while (i < lst->size && cmd->node)
	{
		printf(" node content : %s\n", cmd->node->content);
		printf("avant join : cmdcmd %s\n", cmd->cmd);
		cmd->cmd = ft_strjoin(cmd->node->content, " ");
			printf("apres join : cmdcmd %s\n\n", cmd->cmd);

		if (cmd->node->type == PIPE_LINE)
		{
		// printf("%s\n", cmd->cmd);
			next_cmd = malloc(sizeof(t_cmd));
			next_cmd->node = cmd->node->next;
			next_cmd->next = NULL;
			cmd->next = next_cmd;
			cmd = next_cmd;
		}
		cmd->node = cmd->node->next;
		i++;
	}
}
