/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:30:40 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/05 16:44:43 by thenwood         ###   ########.fr       */
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
	data.nb_input = 0;
	g_sig.status = 0;
	while (1)
	{
		data.nb_cmd = 0;
		init_signals();
		data.nb_input++;
		g_sig.input = readline(ORANGE "\U0001F58A  ~>: " RESET);
		if (!g_sig.input || !ft_strcmp(g_sig.input, "exit"))
		{
			printf("exit\n");
			ft_exit_two(&data);
		}
		else if (!*g_sig.input)
			continue ;
		else
		{
			add_history(g_sig.input);
			data.lex = lexer(g_sig.input);
			if (!error_cmd(data.lex))
			{
				data.envp = get_tab_env(data.env);
				init_parse(&data);
				execution(data.parsed_cmd, data.envp, &data);
				ft_free_tab(data.envp);
				free_lexer(data.lex);
				free_parser(data.cmd, data.parsed_cmd);
			}
			else
				free_lexer(data.lex);
		}
	}
}
