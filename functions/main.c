/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:30:40 by thenwood          #+#    #+#             */
/*   Updated: 2024/02/23 18:26:28 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	sig;

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_data	data;

	(void)av;
	if (ac != 1 || !*env)
		return (1);
	data.env = get_env(env);
	while (1)
	{
		input = readline(ORANGE "\U0001F58A  ~>: " RESET);
		if (input)
			add_history(input);
		data.lex = lexer(input);
		print_list(data.lex);
		printf("capart : %s\n\n", data.lex->head->content);

		parser(data.lex);
	}
	return (0);
}
