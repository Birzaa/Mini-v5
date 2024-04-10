/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:47:48 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/10 12:48:13 by thenwood         ###   ########.fr       */
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
