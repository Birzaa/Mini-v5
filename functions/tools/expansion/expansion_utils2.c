/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:44:20 by abougrai          #+#    #+#             */
/*   Updated: 2024/03/26 15:19:30 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_check_no_sym(t_data *data, t_cmd_word *env, t_cmd_word *word,
		int expanded)
{
	expanded = ft_expand_no_symbol(data->env, word);
	if (!expanded)
	{
		if (!env->state)
		{
			env->content = "";
			env->state = 0;
			word->content = "";
			word->state = 0;
			return ;
		}
		env->state = 2;
	}
	else if (expanded && !word->content)
	{
		env->state = 2;
		env->content = "";
	}
	else
	{
		env->content = "";
		env->state = 0;
	}
}

void	expand(t_cmd_word *cmd, t_data *data)
{
	t_cmd_word	*env;
	t_cmd_word	*word;
	int			symbol;
	int			expanded;

	expanded = 0;
	cmd->type = QOUTE;
	env = cmd;
	word = cmd->next;
	symbol = ft_check_symbol(word->content);
	if (ft_strncmp(word->content, "_", 2) && first_letter(word->content))
		env->type = WORD;
	else if (!ft_strncmp(word->content, "_", 2))
		ft_expand_no_symbol(data->env, word);
	else if (ft_strncmp(word->content, "_", 2) && symbol)
	{
		ft_expand_symbol(data->env, word);
		env->content = "";
	}
	else if (!symbol)
		expand_check_no_sym(data, env, word, expanded);
}

void	expand_whitespace(t_cmd_word *tmp_word)
{
	tmp_word->content = "";
	tmp_word->type = QOUTE;
}

void	while_expand(t_data *data, t_cmd_word *tmp_word)
{
	if (tmp_word->type == ENV && !tmp_word->next)
		tmp_word->type = WORD;
	else if (tmp_word->type == ENV && tmp_word->next
		&& tmp_word->next->type == WORD && tmp_word->state != 1)
		expand(tmp_word, data);
	else if (tmp_word->type == ENV && tmp_word->state == 2
		&& (tmp_word->next->type == DOUBLE_QUOTE
			|| tmp_word->next->type == QOUTE))
		expand_whitespace(tmp_word);
	else if (tmp_word->type == ENV && (tmp_word->state == 1
			|| (tmp_word->next->type == DOUBLE_QUOTE)
			|| tmp_word->next->type == QOUTE
			|| tmp_word->next->type == WHITE_SPACE))
		tmp_word->type = WORD;
}