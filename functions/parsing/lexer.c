/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:35:11 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/08 13:43:54 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_token(char *input, int i, enum e_state *state, t_stack *lst)
{
	if (!is_charset(input[i]))
		i += word_token(*state, input + i, lst);
	else if (input[i] == '\"')
		quote_token(state, input + (i++), lst, 1);
	else if (input[i] == '\'')
		quote_token(state, input + (i++), lst, 2);
	else if (ft_isspace(input[i]))
		lst_add_back(lst, new_node(input + (i++), 1, WHITE_SPACE, *state));
	else if (input[i] == '>' || input[i] == '<')
		i += redir_token(state, input, lst, i);
	else if (input[i] == '|')
		lst_add_back(lst, new_node(input + (i++), 1, PIPE_LINE, *state));
	else if (input[i] == '$')
		lst_add_back(lst, new_node(input + (i++), 1, ENV, *state));
	return (i);
}

t_stack	*lexer(char *input)
{
	int				i;
	enum e_state	state;
	t_stack			*lst;

	i = 0;
	lst = NULL;
	state = GENERAL;
	lst = malloc_lst(lst);
	if (!lst)
		return (NULL);
	while (input[i])
	{
		i = get_token(input, i, &state, lst);
	}
	return (lst);
}
