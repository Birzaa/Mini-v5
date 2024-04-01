/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:22:00 by thomas            #+#    #+#             */
/*   Updated: 2024/03/30 13:14:10 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(char **env, char **valid_cmd, t_data *data, t_pipex *p)
{
	char	*path;
	char	**find_the_path;

	find_the_path = find_path(env);
	path = valid_path(find_the_path, valid_cmd[0]);
	if (execve(path, valid_cmd, env) == -1)
	{
		ft_putstr_fd("Command not found : ", 2);
		ft_putendl_fd(valid_cmd[0], 2);
		free_lexer(data->lex);
		free_parser(data->cmd, data->parsed_cmd);
		free_env(data->env);
		ft_free_tab(data->envp);
		ft_free_tab(find_the_path);
		parent_free(p);
		exit(EXIT_FAILURE);
	}
}
