/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:55:52 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/30 17:51:06 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	index_quote(t_stack *list)
{
	t_node	*node;
	int		i;
	int		index;

	index = 0;
	i = 0;
	node = list->head;
	while (i < list->size)
	{
		if ((node->type == WHITE_SPACE || !is_redir(node->type))
			&& node->state == 2)
			node->index = index++;
		node->index = index;
		node = node->next;
		i++;
	}
}
