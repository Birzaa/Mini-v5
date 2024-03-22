/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:44:26 by abougrai          #+#    #+#             */
/*   Updated: 2024/03/22 02:44:27 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_check_word(t_cmd_word *tmp_word)
{
	if (tmp_word->type == ENV && (!tmp_word->next || tmp_word->state == 1
			|| tmp_word->next))
	{
		tmp_word->type = WORD;
	}
}

void	expand_check_next(t_cmd_word *tmp_word)
{
	if (tmp_word->type == ENV && (!tmp_word->next || tmp_word->state == 0))
	{
		if (!tmp_word->next)
		{
			tmp_word->type = WORD;
			return ;
		}
		if (tmp_word->next->type == DOUBLE_QUOTE && tmp_word->state == 0)
			tmp_word->type = WORD;
	}
}

void	expand_continue(t_cmd_word *tmp_word, int *check)
{
	if (tmp_word->next && tmp_word->next->type == ENV && *check)
	{
		(*check) = 1;
		tmp_word = tmp_word->next;
	}
}
