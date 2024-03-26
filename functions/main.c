/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:30:40 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/26 17:59:07 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal	g_sig;


int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	**envp;

	envp = NULL;
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
			if (!ft_strcmp(g_sig.input, "exit"))
				ft_exit(&data);
			data.lex = lexer(g_sig.input);
			envp = get_tab_env(data.env);
			init_parse(&data);
			execution(data.parsed_cmd, env, &data);
			ft_free_tab(envp);
		}
	}
}
