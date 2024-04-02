/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 09:11:53 by abougrai          #+#    #+#             */
/*   Updated: 2024/04/01 09:18:37 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_case_one(t_cmd_word *tmp_word)
{
	tmp_word->type = WHITE_SPACE;
	tmp_word = tmp_word->next;
	free(tmp_word->content);
	tmp_word->content = ft_strdup("");
	tmp_word->type = WORD;
}

void	quote_case_two(t_cmd_word *tmp_word)
{
	tmp_word->type = WHITE_SPACE;
	tmp_word = tmp_word->next;
	free(tmp_word->content);
	tmp_word->content = ft_strdup("");
	tmp_word->type = WORD;
}
