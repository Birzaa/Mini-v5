/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:30:40 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/05 16:36:48 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal	g_sig;

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		printf("%s\n", tab[i++]);
}
int	main(int ac, char **av, char **env)
{
	char	*input;
	char	*exit;
	t_data	data;
	char	**test;

	test = NULL;
	exit = "exit";
	input = NULL;
	/* char	str[] = "BONJOUR=capart";
	char	str1[] = "BONJOUR=hello"; */
	(void)data;
	(void)av;
	(void)env;
	if (ac != 1)
		return (1);
	/* 	else if (!*env)
			data.env = create_env(); */
	data.env = get_env(env);
	while (1)
	{
		input = readline(ORANGE "\U0001F58A  ~>: " RESET);
		if (input)
			add_history(input);
		if (!ft_strcmp(input, exit))
			ft_exit(&data); /*
			if (!ft_strcmp(input, "export"))
				export_no_arg(data.env);
			if (!ft_strcmp(input, "env"))
				print_env(data.env);
			if (!ft_strncmp(input, "export BONJOUR=capart", 21))
				export(&data.env, str);
			if (!ft_strncmp(input, "export BONJOUR=hello", 21))
				export(&data.env, str1);
			if (!ft_strncmp(input, "unset BONJOUR", 13))
				unset(data.env, "BONJOUR"); */
		data.lex = lexer(input);
		if (!error_cmd(data.lex))
		{
			test = get_tab_env(data.env);
			data.cmd = parser(data.lex);
			parse(&data);
			//exec(data.cmd, test, &data);
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
