/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:47:48 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/13 13:18:59 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_one_node(t_cmd_word **current, t_data *data, int check)
{
	if (check == 1)
	{
		data->count += c_words((*current)->content, ' ');
	}
	else
	{
		data->count++;
	}
	if ((*current)->next)
		(*current) = (*current)->next;
	else
		return (1);
	return (0);
}

void	skip_space(t_cmd_word **cmd)
{
	while ((*cmd)->next && (*cmd)->type == WHITE_SPACE)
		(*cmd) = (*cmd)->next;
}
