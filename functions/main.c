/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:30:40 by thenwood          #+#    #+#             */
/*   Updated: 2024/02/25 05:08:20 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal	g_sig;

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_data	data;
	int		i;

	i = 0;
	(void)data;
	(void)av;
	(void)i;
	if (ac != 1 || !*env)
		return (1);
	data.env = get_env(env);
	while (1)
	{
		input = readline(ORANGE "\U0001F58A  ~>: " RESET);
		if (input)
			add_history(input);
		if (!ft_strcmp(input, "exit"))
		{
			free_env(data.env);
			exit(0);
		}
		if (!ft_strcmp(input, "export"))
			export_no_arg(data.env);
		if (!ft_strcmp(input, "env"))
			print_env(data.env);
	}
	return (0);
}
