/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:30:40 by thenwood          #+#    #+#             */
/*   Updated: 2024/02/21 15:45:19 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_data	data;

	(void)av;
	if (ac != 1 || !*env)
		return (1);
	while (1)
	{
		input = readline(ORANGE "\U0001F58A  ~>: " RESET);
		if (input)
			add_history(input);
		data.lex = lexer(input);
		print_list(data.lex);
	}
	return (0);
}
