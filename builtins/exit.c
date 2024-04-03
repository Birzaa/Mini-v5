/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:43:41 by abougrai          #+#    #+#             */
/*   Updated: 2024/04/03 15:34:06 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit_non_digit(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if ((command[0] == '-' || command[0] == '+') && command[0 + 1])
			ft_nothing();
		else if (!ft_isdigit(command[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_get_exit_atoi(char *command)
{
	int	exit;

	exit = 0;
	exit = ft_atoi(command);
	if (ft_exit_non_digit(command) && exit == 0)
		exit = 2;
	else if (exit > 255)
		exit = exit % 256;
	else if (exit < 0)
		exit = 256 + (exit % 256);
	return (exit);
}

void	ft_exit(t_data *data, t_pipex *p, char **command)
{
	int	i;

	g_sig.status = 0;
	i = ft_tab_len(command);
	if (i > 2 && !ft_exit_non_digit(command[1])
		&& ft_exit_non_digit(command[2]))
	{
		g_sig.status = 1;
		return ((void)printf("bash: exit: too many arguments\n"));
	}
	else if (i > 1 && ft_exit_non_digit(command[1]))
	{
		printf("bash: exit: %s: numeric argument required\n", command[1]);
		g_sig.status = 1;
	}
	if (command[1])
		g_sig.status = ft_get_exit_atoi(command[1]);
	free_env(data->env);
	free_lexer(data->lex);
	clear_history();
	ft_free_tab(data->envp);
	free_parser(data->cmd, data->parsed_cmd);
	parent_free(p);
	exit(g_sig.status);
}

void	ft_exit_two(t_data *data)
{
	free_env(data->env);
	// free_lexer(data->lex);
	clear_history();
	// ft_free_tab(data->envp);
	// free_parser(data->cmd, data->parsed_cmd);
	exit(g_sig.status);
}
