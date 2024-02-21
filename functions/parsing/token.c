/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:52:18 by thenwood          #+#    #+#             */
/*   Updated: 2024/02/21 13:23:45 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_token(enum e_state state, char *input, t_stack *lst)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	lst_add_back(lst, new_node(input, i, WORD, state));
	return (i);
}
