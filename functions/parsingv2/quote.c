/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:28:17 by thomas            #+#    #+#             */
/*   Updated: 2024/03/11 10:57:46 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_into_single_word(t_cmd_word **cmd)
{
	char	*tmp;
	enum e_state state = (*cmd)->state;

	tmp = "";
	while ((*cmd))
	{
		if ((*cmd)->state != state && (*cmd)->type == WHITE_SPACE)
			break ;
		tmp = ft_strjoin(tmp, (*cmd)->content);
		(*cmd)->content = " ";
		(*cmd)->type = WHITE_SPACE;
		if ((*cmd)->next)
			(*cmd) = (*cmd)->next;
		else
			break;
	}
	(*cmd)->content = ft_strdup(tmp);
	(*cmd)->type = WORD;
}

void	parsing_quote(t_cmd *cmd)
{
	t_cmd		*head;
	t_cmd_word	*tmp_word;

	head = cmd;
	while (head)
	{
		tmp_word = head->words;
		while (tmp_word)
		{
			if ((tmp_word->type == DOUBLE_QUOTE || tmp_word->type == QOUTE))
			{
				tmp_word->type = WHITE_SPACE;
			}
			if (tmp_word->state != GENERAL)
			{
				split_into_single_word(&tmp_word);
			}
			tmp_word = tmp_word->next;
		}
		head = head->next;
	}
}
