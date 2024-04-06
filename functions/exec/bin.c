/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:22:00 by thomas            #+#    #+#             */
/*   Updated: 2024/04/06 14:15:54 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(char **env, char **valid_cmd, t_data *data, t_pipex *p)
{
	char		*path;
	char		**find_the_path;
	struct stat	path_stat;

	find_the_path = find_path(env);
	path = valid_path(find_the_path, valid_cmd[0]);
	if (execve(path, valid_cmd, env) == -1)
	{
		if (access(valid_cmd[0], F_OK | X_OK) == -1 && !ft_strncmp(valid_cmd[0],
				"./", 2))
		{
			handle_error(valid_cmd[0], strerror(errno));
			free_lexer(data->lex);
			free_parser(data->cmd, data->parsed_cmd);
			free_env(data->env);
			ft_free_tab(data->envp);
			ft_free_tab(find_the_path);
			parent_free(p);
			exit(127);
		}
		else if (stat(valid_cmd[0], &path_stat) == 0
			&& (!ft_strncmp(valid_cmd[0], "/", 1) || !ft_strncmp(valid_cmd[0],
				"./", 2)))
		{
			ft_putstr_fd("bash: ",2);
			ft_putstr_fd(valid_cmd[0],2);
			ft_putstr_fd(" Is a directory\n",2);
			exit(126);
		}
		else
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(valid_cmd[0], 2);
			ft_putstr_fd(" command not found\n", 2);
			free_lexer(data->lex);
			free_parser(data->cmd, data->parsed_cmd);
			free_env(data->env);
			ft_free_tab(data->envp);
			ft_free_tab(find_the_path);
			parent_free(p);
			exit(127);
		}
	}
}
