/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:22:00 by thomas            #+#    #+#             */
/*   Updated: 2024/04/02 12:28:15 by abougrai         ###   ########.fr       */
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
		// printf("%d\n", g_sig.status);
		// g_sig.status = 127;
		exit(g_sig.status);
	}
}
