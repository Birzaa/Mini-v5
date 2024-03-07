/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:30:40 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/07 08:08:13 by abougrai         ###   ########.fr       */
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
	(void)data;
	(void)av;
	(void)env;
	(void)envp;
	if (ac != 1)
		return (1);
	/* 	else if (!*env)
			data.env = create_env(); */
	data.env = get_env(env);
	init_signals();
	while (1)
	{
		printf("%d\n", g_sig.pid);
		input = readline(ORANGE "\U0001F58A  ~>: " RESET);
		if (!*input)
			ft_nothing();
		else 
		{
			add_history(input);
			if (!ft_strcmp(input, "exit"))
				ft_exit(&data);
			data.lex = lexer(input);
			if (!error_cmd(data.lex))
			{
				envp = get_tab_env(data.env);
				data.cmd = parser(data.lex);
				/* print_cmd_list(data.cmd); */
				exec(data.cmd, envp, &data);
				ft_free_tab(envp);
				/*
					EXECUTION
					WAIT
					free lexer + parser
					*/
			}
			else
			{
				/* free le lexer */
			}
		}
	}
}
