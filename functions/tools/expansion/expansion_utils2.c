/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:44:20 by abougrai          #+#    #+#             */
/*   Updated: 2024/03/22 02:44:21 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_check_letter(t_cmd_word *tmp_word, int *check)
{
	(void)check;
	if (tmp_word->type == ENV && (first_letter(tmp_word->next->content))
		&& ft_strncmp(tmp_word->next->content, "_", 2)
		&& tmp_word->next->state != 0)
	{
		tmp_word->type = WORD;
		tmp_word = tmp_word->next;
	}
}

void	expand_check_quote(t_cmd_word *tmp_word)
{
	if (tmp_word->type == ENV && tmp_word->next
		&& (tmp_word->next->type == QOUTE
			|| tmp_word->next->type == DOUBLE_QUOTE) && tmp_word->state != 0)
	{
		tmp_word->content = "";
	}
}

void	expand_check_expand(t_data *data, t_cmd_word *tmp_word, int *check)
{
	if (tmp_word->type == ENV && tmp_word->state != 1 && tmp_word->next)
	{
		tmp_word->type = WHITE_SPACE;
		if (tmp_word->type == ENV && tmp_word->state == 2
			&& tmp_word->next->type == DOUBLE_QUOTE)
			tmp_word->type = WORD;
		if (check)
		{
			tmp_word->type = WORD;
		}
		tmp_word->content = "";
		expand(tmp_word, data);
		if (tmp_word->next)
			tmp_word = tmp_word->next;
		(*check) = 1;
	}
}
