/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:28:17 by thomas            #+#    #+#             */
/*   Updated: 2024/03/14 13:01:54 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nb_word_in_quote(t_cmd_word *cmd, enum e_state state)
{
	t_cmd_word		*head;
	unsigned int	count;

	head = cmd;
	count = 0;
	while (head)
	{
		if (state == head->state)
			count++;
		if (head->state == GENERAL && head->type == WHITE_SPACE)
			break ;
		head = head->next;
	}
	printf("count : %d\n", count);
	return (count);
}

void	put_in_one_word(t_cmd_word **cmd, unsigned int nb)
{
	char		*tmp;
	unsigned			i;

	i = 0;
	tmp = "";
	while (i < nb)
	{
		tmp = ft_strjoin(tmp, (*cmd)->content);
		(*cmd)->content = "";
		(*cmd)->type = WHITE_SPACE;
		i++;
		(*cmd) = (*cmd)->next;
	}
	printf("actuel content : %s\n", (*cmd)->content);
	(*cmd)->content = tmp;
	(*cmd)->type = WORD;
	printf("Copie : %s\n", tmp);
}

void	parsing_quote(t_cmd *cmd)
{
	t_cmd			*head;
	t_cmd_word		*tmp_word;
	enum e_state	state;
	unsigned int	nb;

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
				nb = nb_word_in_quote(tmp_word, state);
				put_in_one_word(&tmp_word, nb);
			}
			tmp_word = tmp_word->next;
		}
		head = head->next;
	}
}
