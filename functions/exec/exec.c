/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:02:46 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/06 12:57:21 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char	**get_cmd(t_cmd *head)
{
	t_cmd		*current;
	t_cmd_word	*word;
	char		**cmd;
	int			i;

	i = 0;
	current = head;
	cmd = malloc(sizeof(char *) * 3);
	if (!cmd)
		return (NULL);
	if (current)
	{
		word = current->words;
		while (word)
		{
			if (word->type == REDIR_OUT || word->type == DREDIR_OUT)
			{
				cmd[i++] = NULL;
				return (cmd);
			}
			if (word->type == WORD)
			{
				cmd[i] = malloc(ft_strlen(word->content) + 1);
				if (!cmd[i])
				{
					ft_free_tab(cmd);
					return (NULL);
				}
				cmd[i] = ft_strdup(word->content);
				i++;
			}
			word = word->next;
		}
		cmd[i] = NULL;
	}
	cmd[i] = NULL;
	return (cmd);
}

void	execute_cmd(char **env, char **valid_cmd)
{
	char	*path;
	char	**find_the_path;

	find_the_path = find_path(env);
	path = valid_path(find_the_path, valid_cmd[0]);
	if (execve(path, valid_cmd, env) == -1)
	{
		ft_putstr_fd("Command not found : ", 2);
		ft_putendl_fd(valid_cmd[0], 2);
		ft_free_tab(valid_cmd);
		ft_free_tab(find_the_path);
		exit(EXIT_FAILURE);
	}
}

void	execute_builtin(t_cmd *cmd, char **command, t_data *data)
{
	if (ft_strcmp(command[0], "cd") == 0)
		ft_cd(command[1], data);
	else if (ft_strcmp(command[0], "pwd") == 0)
		ft_pwd(cmd);
	else if (ft_strcmp(command[0], "cd") == 0)
		ft_cd(command[1], data);
	else if (ft_strcmp(command[0], "export") == 0)
	{
		if (!command[1])
		{
			export_no_arg(data->env);
			return ;
		}
		export(&data->env, command[1]);
	}
	else if (ft_strcmp(command[0], "env") == 0)
		print_env(data->env);
	else if (ft_strcmp(command[0], "unset") == 0)
	{
		if (!command[1])
			return ;
		unset(data->env, command[1]);
	}
}

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}

void	exec(t_cmd *cmd, char **env, t_data *data)
{
	char			**command;
	pid_t			pid;
	int				status;
	t_redir_list	*redir;
	t_redir_in		r_in;

	number_redir_in(cmd, &r_in);
	command = get_cmd(cmd);
	redir = parsing_redir(cmd);
	redirection_out(cmd, redir);
	(void)redir;
	if (is_builtin(command[0]))
	{
		if (r_in.size)
			open_redir_in(&r_in);
		execute_builtin(cmd, command, data);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			fprintf(stderr, "Erreur lors de la création du processus fils.\n");
		// MODIFIER ERREUR VALEUR RETOUR
		else if (pid == 0)
		{
			if (r_in.size)
				open_redir_in(&r_in);
			execute_cmd(env, command);
		}
		else
			waitpid(pid, &status, 0);
	}
	if (cmd->fd)
	{
		close(cmd->fd);
		dup2(cmd->saved_stdout, STDOUT_FILENO);
	}
}
