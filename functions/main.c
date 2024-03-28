/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:30:40 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/28 17:51:22 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal	g_sig;


int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)av;
	if (ac != 1)
		return (1);
	if (!*env)
		env = create_env();
	data.env = get_env(env);
	init_signals();
	g_sig.status = 0;
	while (1)
	{
		g_sig.input = readline(ORANGE "\U0001F58A  ~>: " RESET);
		if (!g_sig.input)
		{
			printf("exit\n");
			ft_exit(&data);
		}
		else if (!*g_sig.input)
			ft_nothing();
		else
		{
			add_history(g_sig.input);
			data.lex = lexer(g_sig.input);
			if (!error_cmd(data.lex))
			{
				data.envp = get_tab_env(data.env);
				init_parse(&data);
				if (!strcmp(g_sig.input, "exit"))
				{
					free_env(data.env);
					free_lexer(data.lex);
					clear_history();
					ft_free_tab(data.envp);
					free_parser(data.cmd, data.parsed_cmd);
					exit(0);
				}
				execution(data.parsed_cmd, env, &data);
				ft_free_tab(data.envp);
				free_lexer(data.lex);
				free_parser(data.cmd, data.parsed_cmd);
			}
			else
				free_lexer(data.lex);
		}
	}
}
