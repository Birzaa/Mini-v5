/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:28:17 by thomas            #+#    #+#             */
/*   Updated: 2024/04/04 19:10:42 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	next_is_not_a_word(t_cmd_word *cmd2, char *tmp)
{
	if ((cmd2->next->type == WHITE_SPACE || is_redir(cmd2->next->type))
		&& cmd2->next->state == GENERAL)
	{
		free(cmd2->content);
		cmd2->content = ft_strdup(tmp);
		cmd2->type = WORD;
		free(tmp);
		return (1);
	}
	return (0);
}

void	put_in_one_word_two(t_cmd_word *cmd2, char *tmp)
{
	int	need_free;

	need_free = 0;
	if (cmd2->type == WORD)
	{
		need_free = 1;
		tmp = ft_strjoin(tmp, cmd2->content);
		cmd2->type = WHITE_SPACE;
		if (cmd2->next)
			cmd2 = cmd2->next;
	}
	free(cmd2->content);
	cmd2->content = ft_strdup(tmp);
	if (need_free)
		free(tmp);
	cmd2->type = WORD;
}

void	put_in_one_word(t_cmd_word **cmd, int index)
{
	char		*tmp;
	t_cmd_word	*cmd2;
	char		*old_tmp;

	cmd2 = *cmd;
	tmp = ft_strdup("");
	while (cmd2->next && cmd2->index == index)
	{
		if (cmd2->state != 2 || cmd2->type == WORD)
		{
			old_tmp = tmp;
			tmp = ft_strjoin(tmp, cmd2->content);
			free(old_tmp);
		}
		cmd2->type = WHITE_SPACE;
		if (next_is_not_a_word(cmd2, tmp))
			return ;
		cmd2 = cmd2->next;
	}
	put_in_one_word_two(cmd2, tmp);
	free(tmp);
}

void	quote_next_to_quote(t_cmd_word *tmp_word)
{
	int	check;

	check = 0;
	if ((tmp_word->type == DOUBLE_QUOTE || tmp_word->type == QOUTE))
	{
		if (tmp_word->type == DOUBLE_QUOTE)
			check = 0;
		if (tmp_word->type == QOUTE)
			check = 1;
		if (tmp_word->next && tmp_word->next->type == DOUBLE_QUOTE && !check)
			quote_case_one(tmp_word);
		else if (tmp_word->next && tmp_word->next->type == QOUTE && check)
			quote_case_two(tmp_word);
		else
			tmp_word->type = WHITE_SPACE;
	}
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
			if (tmp_word->next && (tmp_word->state != GENERAL
					|| (tmp_word->type == WORD
						&& (tmp_word->next->type != WHITE_SPACE
							&& !is_redir(tmp_word->next->type))))
				&& (tmp_word->type == WORD || tmp_word->type == QOUTE
					|| tmp_word->type == DOUBLE_QUOTE
					|| tmp_word->type == PIPE_LINE || is_redir(tmp_word->type)))
				put_in_one_word(&tmp_word, tmp_word->index);
			quote_next_to_quote(tmp_word);
			if (tmp_word->next)
				tmp_word = tmp_word->next;
			else
				break ;
		}
		head = head->next;
	}
}
