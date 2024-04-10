/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:30:40 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/10 09:07:51 by abougrai         ###   ########.fr       */
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
		init_signals();
		data.nb_input++;
		data.tab_created = 0;
		g_sig.input = readline("~~>: ");
		if (!g_sig.input)
		{
			ft_putstr_fd("exit\n", 2);
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
