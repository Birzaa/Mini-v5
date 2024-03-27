/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:30:40 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/27 18:46:52 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal	g_sig;

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*input;
	char	**envp;

	envp = NULL;
	input = NULL;
	(void)av;
	(void)envp;
	if (ac != 1)
		return (1);
	/* 	else if (!*env)
			data.env = create_env(); */
	data.env = get_env(env);
	/* 	init_signals(); */
	g_sig.status = 0;
	while (1)
	{
		// printf("%d\n", g_sig.pid);
		input = readline(ORANGE "\U0001F58A  ~>: " RESET);
		if (!*input)
			ft_nothing();
		else
		{
			add_history(input);
			data.lex = lexer(input);
			if (!error_cmd(data.lex))
			{
				envp = get_tab_env(data.env);
				init_parse(&data);
				if (!strcmp(input, "exit"))
				{
					free_env(data.env);
					free_lexer(data.lex);
					clear_history();
					ft_free_tab(envp);
					free_parser(data.cmd, data.parsed_cmd);
					exit(0);
				}
				execution(data.parsed_cmd, env, &data);
				ft_free_tab(envp);
				free_lexer(data.lex);
				free_parser(data.cmd, data.parsed_cmd);
			}
			else
				free_lexer(data.lex);
		}
	}
}
