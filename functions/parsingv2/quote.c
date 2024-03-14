/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:28:17 by thomas            #+#    #+#             */
/*   Updated: 2024/03/14 18:29:46 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_in_one_word(t_cmd_word **cmd, int index)
{
	char		*tmp;
	t_cmd_word	*cmd2;

	cmd2 = *cmd;
	tmp = "";
	while (cmd2->next && cmd2->index == index)
	{
		if (cmd2->state != 2 || cmd2->type == WORD)
		{
			tmp = ft_strjoin(tmp, cmd2->content);
		}
		cmd2->content = "";
		cmd2->type = WHITE_SPACE;
		cmd2 = cmd2->next;
	}
	if (cmd2->type == WORD)
	{
		tmp = ft_strjoin(tmp, cmd2->content);
		cmd2->content = "";
		cmd2->type = WHITE_SPACE;
		if (cmd2->next)
			cmd2 = cmd2->next;
	}
	cmd2->content = tmp;
	cmd2->type = WORD;
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
			if (tmp_word->state != GENERAL && (tmp_word->type == WORD
					|| tmp_word->type == QOUTE
					|| tmp_word->type == DOUBLE_QUOTE))
			{
				put_in_one_word(&tmp_word, tmp_word->index);
			}
			if ((tmp_word->type == DOUBLE_QUOTE || tmp_word->type == QOUTE))
			{
				tmp_word->type = WHITE_SPACE;
			}
			tmp_word = tmp_word->next;
		}
		head = head->next;
	}
}
