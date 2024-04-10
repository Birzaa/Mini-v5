/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:30:40 by thenwood          #+#    #+#             */
/*   Updated: 2024/04/10 12:52:43 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal	g_sig;

void	init_data(t_data *data, char **env)
{
	if (!*env)
		env = create_env();
	data->env = get_env(env);
	data->tab_created = 0;
	data->nb_input = 0;
	data->i = 0;
	data->count = 0;
	g_sig.status = 0;
}

void	init_exec(t_data *data)
{
	data->envp = get_tab_env(data->env);
	init_parse(data);
	execution(data->parsed_cmd, data->envp, data);
	ft_free_tab(data->envp);
	free_lexer(data->lex);
	free_parser(data->cmd, data->parsed_cmd);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)av;
	if (ac != 1 || !isatty(0))
		return (1);
	init_data(&data, env);
	while (1)
	{
		init_signals();
		data.nb_input++;
		g_sig.input = readline(ORANGE "~~>: " RESET);
		if (!g_sig.input)
			(ft_putstr_fd("exit\n", 2), ft_exit_two(&data));
		else if (!*g_sig.input)
			continue ;
		else
		{
			add_history(g_sig.input);
			data.lex = lexer(g_sig.input);
			if (!error_cmd(data.lex))
				init_exec(&data);
			else
				free_lexer(data.lex);
		}
	}
}
