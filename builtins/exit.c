/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:43:41 by abougrai          #+#    #+#             */
/*   Updated: 2024/04/01 07:31:07 by abougrai         ###   ########.fr       */
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
