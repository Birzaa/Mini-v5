/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:28:17 by thomas            #+#    #+#             */
/*   Updated: 2024/03/13 17:49:47 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_into_single_word(t_cmd_word **cmd, enum e_state state)
{
	char	*str;

	str = "";
	while ((*cmd)->state == state && (*cmd))
	{
		str = ft_strjoin(str, (*cmd)->content);
		(*cmd)->content = "";
		(*cmd)->type = WHITE_SPACE;
		(*cmd) = (*cmd)->next;
	}
	while ((*cmd)->next && ((*cmd)->next->type == WORD
			|| (*cmd)->next->type == QOUTE
			|| (*cmd)->next->type == DOUBLE_QUOTE))
	{
		if (((*cmd)->next->type == QOUTE || (*cmd)->next->type == DOUBLE_QUOTE)
			&& (*cmd)->next->state != state && (*cmd)->next->next)
			(*cmd) = (*cmd)->next;
		printf("Content : %s\n", (*cmd)->content);
		printf("Next Content : %s\n", (*cmd)->next->content);
		if ((*cmd)->next->state == 0 || (*cmd)->next->state == 1)
		{
			str = ft_strjoin(str, (*cmd)->next->content);
			printf("str dans la bocle = %s\n", (str));
			(*cmd)->next->content = "";
			(*cmd)->next->type = WHITE_SPACE;
		}
		else if ((*cmd)->next->type != WHITE_SPACE)
		{
			str = ft_strjoin(str, (*cmd)->content);
			(*cmd)->next->content = "";
			(*cmd)->next->type = WHITE_SPACE;
		}
		(*cmd) = (*cmd)->next;
		while ((*cmd)->next && (*cmd)->next->type == WHITE_SPACE)
		{
			str = ft_strjoin(str, (*cmd)->next->content);
			(*cmd) = (*cmd)->next;
		}
	}
	printf("str = %s\n", (str));
	(*cmd)->content = str;
	(*cmd)->type = WORD;
}

void	parsing_quote(t_cmd *cmd)
{
	t_cmd			*head;
	t_cmd_word		*tmp_word;
	enum e_state	state;

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
			state = tmp_word->state;
			if (tmp_word->state != GENERAL)
			{
				split_into_single_word(&tmp_word, state);
			}
			tmp_word = tmp_word->next;
		}
		head = head->next;
	}
}
