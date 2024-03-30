/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:43:41 by abougrai          #+#    #+#             */
/*   Updated: 2024/03/30 14:02:50 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_data *data, t_pipex *p)
{
	free_env(data->env);
	free_lexer(data->lex);
	clear_history();
	ft_free_tab(data->envp);
	free_parser(data->cmd, data->parsed_cmd);
	parent_free(p);
	exit(0);
}

void	ft_exit_two(t_data *data)
{
	free_env(data->env);
	// free_lexer(data->lex);
	clear_history();
	// ft_free_tab(data->envp);
	// free_parser(data->cmd, data->parsed_cmd);
	exit(0);
}
