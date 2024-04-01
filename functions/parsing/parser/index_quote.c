/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:55:52 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/01 19:52:09 by thomas           ###   ########.fr       */
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
		if (((node->type == WHITE_SPACE || is_redir(node->type)) && node->state == 2))
			node->index = index++;
		node->index = index;
		node = node->next;
		i++;
	}
}
