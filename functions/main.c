/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:30:40 by thenwood          #+#    #+#             */
/*   Updated: 2024/02/24 16:56:43 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	sig;

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_data	data;

	(void)data;
	(void)av;
	if (ac != 1 || !*env)
		return (1);
	data.env = get_env(env);
	while (1)
	{
		input = readline(ORANGE "\U0001F58A  ~>: " RESET);
		if (input)
			add_history(input);
		if (!ft_strcmp(input, "env"))
		{
			print_env(data.env);
		}
		data.lex = lexer(input);
		/* print_list(data.lex); */
		/* parser(data.lex); */
	}
	return (0);
}
