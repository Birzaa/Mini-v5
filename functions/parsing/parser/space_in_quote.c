/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_in_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:56:30 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/15 14:01:32 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_space_in_quote(t_stack *list)
{
	t_node	*node;
	int		i;

	i = 0;
	node = list->head;
	while (i < list->size)
	{
		if (node->type == WHITE_SPACE && node->state != 2)
			node->type = WORD;
		node = node->next;
		i++;
	}
}
