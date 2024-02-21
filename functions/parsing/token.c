/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:52:18 by thenwood          #+#    #+#             */
/*   Updated: 2024/02/21 15:20:21 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_token(enum e_state state, char *input, t_stack *lst)
{
	int	i;

	i = 0;
	while (!is_charset(input[i]))
		i++;
	lst_add_back(lst, new_node(input, i, WORD, state));
	return (i);
}
/* 
	1 = DQUOTE
*/
void	quote_token(enum e_state *state, char *input, t_stack *lst, int quote)
{
	enum e_state	e_state;
	enum e_token	e_type;

	if (quote == 1)
	{
		e_state = IN_DQUOTE;
		e_type = DOUBLE_QUOTE;
	}
	else
	{
		e_state = IN_QUOTE;
		e_type = QOUTE;
	}
	if (*state == GENERAL)
	{
		lst_add_back(lst, new_node(input, 1, e_type, *state));
		*state = e_state;
	}
	else if (*state == e_state)
	{
		*state = GENERAL;
		lst_add_back(lst, new_node(input, 1, e_type, *state));
	}
	else
		lst_add_back(lst, new_node(input, 1, e_type, *state));
}
