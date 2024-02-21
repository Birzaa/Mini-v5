/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:30:40 by thenwood          #+#    #+#             */
/*   Updated: 2024/02/21 15:02:36 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_data	data;

	data.env = get_env(env);
	(void)av;
	if (ac != 1 || !*env)
		return (1);
	while (1)
	{
		input = readline(ORANGE "\U0001F58A  ~>: " RESET);
		if (input)
			add_history(input);
		free(input);
	}
	return (0);
}
