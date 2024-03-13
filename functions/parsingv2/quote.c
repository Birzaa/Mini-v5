/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:28:17 by thomas            #+#    #+#             */
/*   Updated: 2024/03/13 12:25:32 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_into_single_word(t_cmd_word **cmd, enum e_token token)
{
	char		*tmp;
	int			loop;
	t_cmd_word	*cmd2;

	loop = 0;
	cmd2 = *cmd;
	(void)token;
	tmp = "";
	while (cmd2 && cmd2->state == IN_DQUOTE)
	{
		printf("content [%s]\n", cmd2->content);
		loop++;
		tmp = ft_strjoin(tmp, cmd2->content);
		if (cmd2->next->state == IN_DQUOTE)
			cmd2 = cmd2->next;
		else
			break ;
	}
	cmd2->content = ft_strdup(tmp);
	printf("final [%s]\n", cmd2->content);
	cmd2->type = WORD;
}

void	parsing_quote(t_cmd *cmd)
{
	int				test;
	t_cmd			*head;
	t_cmd_word		*tmp_word;
	enum e_token	token;
	char			*tmp;

	tmp = "";
	test = 0;
	head = cmd;
	token = 0;
	while (head)
	{
		tmp_word = head->words;
		while (tmp_word)
		{
			printf("loop [%d] content : {%s} token %c\n", test++,
				tmp_word->content, (char)token);
			if ((tmp_word->type == DOUBLE_QUOTE || tmp_word->type == QOUTE))
			{
				tmp_word->type = WHITE_SPACE;
			}
			if (tmp_word->state != GENERAL)
			{
				split_into_single_word(&tmp_word, 0);
			}
			else
				tmp_word = tmp_word->next;
		}
		head = head->next;
	}
}

/* void	parsing_quote(t_cmd *cmd)
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
				split_into_single_word(&tmp_word, 0);
			}
			tmp_word = tmp_word->next;
		}
		head = head->next;
	}
} */

/* void	split_into_single_word(t_cmd_word **cmd, enum e_token token)
{
	char		*tmp;
	t_cmd_word	*cmd2;

	cmd2 = *cmd;
	(void)token;
	tmp = "";
	while (cmd2)
	{
		printf("content [%s]\n", cmd2->content);
		if (cmd2->state == GENERAL && cmd2->type == WHITE_SPACE)
		{
			printf("capart\n");
			return ;
		}
		if (cmd2->state != 2 || cmd2->type == WORD)
		{
			tmp = ft_strjoin(tmp, cmd2->content);
			cmd2->content = "";
			cmd2->type = WHITE_SPACE;
		}
		if (cmd2->state == 0 && cmd2->next->type == DOUBLE_QUOTE)
		{
			if (cmd2->next->type == DOUBLE_QUOTE)
			{
				if (cmd2->next)
				{
					cmd2 = cmd2->next;
				}
				while (cmd2->type == DOUBLE_QUOTE && cmd2)
				{
					if (cmd2->next)
					{
						cmd2 = cmd2->next;
					}
					else
					{
						break ;
					}
				}
			}
		}
		if (cmd2->state == 1 && cmd2->next->type == QOUTE)
		{
			if (cmd2->next->type == QOUTE && cmd2->next->next->type == QOUTE)
			{
				if (cmd2->next)
					cmd2 = cmd2->next;
				while (cmd2->type == QOUTE && cmd2)
				{
					if (cmd2->next)
					{
						cmd2 = cmd2->next;
					}
					else
						break ;
				}
			}
		}
		if (cmd2->state == GENERAL && cmd2->type == WHITE_SPACE)
		{
			break ;
		}
		if ((cmd2)->next)
			cmd2 = cmd2->next;
		else
			break ;
	}
	cmd2->content = ft_strdup(tmp);
	cmd2->type = WORD;
} */
