/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:30:40 by thenwood          #+#    #+#             */
/*   Updated: 2024/02/25 22:06:46 by thenwood         ###   ########.fr       */
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
		if (!error_cmd(data.lex))
		{
			parser(data.lex);
			/* EXECUTION
				WAIT
			*/
			free_list(data.lex);
		}
		else
			free_list(data.lex);
			
	}
	return (0);
}
