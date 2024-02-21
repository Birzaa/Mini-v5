/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:35:11 by thenwood          #+#    #+#             */
/*   Updated: 2024/02/21 13:46:57 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_token(char *input, int i, enum e_state *state, t_stack *lst)
{
	if (!is_charset(input[i]))
		i += word_token(*state, input, lst);
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
