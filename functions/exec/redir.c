/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:04:14 by thomas            #+#    #+#             */
/*   Updated: 2024/03/27 20:16:08 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*here_doc(char *av, t_pipex *pipex, int index)
{
	int		file;
	char	*buf;
	char	*name_file;
	char	*index_str;

	index_str = ft_itoa(index);
	name_file = ft_strjoin(av, index_str);
	free(index_str);
	pipex->h_doc_name[index] = ft_strdup(name_file);
	if (!pipex->h_doc_name[index])
	{
		ft_free_tab(pipex->h_doc_name);
		free(name_file);
		return (NULL);
	}
	file = open(name_file, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
	{
		free(name_file);
		free(pipex->h_doc_name[index]);
		return (NULL);
	}
	while (1)
	{
		buf = readline("\033[1;34m~> \033[0m");
		if (!buf)
			return (NULL);
		if (!ft_strcmp(av, buf))
		{
			free(buf);
			break ;
		}
		write(file, buf, ft_strlen(buf));
		write(file, "\n", 1);
		free(buf);
	}
	close(file);
	free(name_file);
	return (pipex->h_doc_name[index]);
}

void	open_redir_in(t_command *head, t_pipex *pipex)
{
	t_redir_in_2	*tmp;

	pipex->infile = pipex->saved_in;
	tmp = head->parsed_cmd->r_in;
	while (tmp)
	{
		if (!tmp->h_doc)
			pipex->infile = open(tmp->file, O_RDONLY, 0644);
		else
		{
			pipex->h_doc = 1;
			pipex->infile = open(tmp->file, O_RDONLY, 0644);
		}
		if (pipex->infile == -1)
		{
			printf("Impossible de in\n");
			exit(1);
		}
		tmp = tmp->next;
	}
}

void	open_redir_out(t_command *head, t_pipex *pipex)
{
	t_redir_out	*tmp;

	tmp = head->parsed_cmd->r_out;
	pipex->outfile = pipex->saved_out;
	while (tmp)
	{
		if (!tmp->append)
			pipex->outfile = open(tmp->file,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			pipex->outfile = open(tmp->file,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (pipex->outfile == -1)
		{
			printf("Impossible de out\n");
			exit(1);
		}
		tmp = tmp->next;
	}
}

void	nb_h_doc(t_command *parsed_cmd, t_pipex *pipex)
{
	t_command		*current_cmd;
	t_redir_in_2	*r_in;

	pipex->nb_h_doc = 0;
	current_cmd = parsed_cmd;
	while (pipex->idx < pipex->nb_cmd)
	{
		if (current_cmd->parsed_cmd->r_in)
		{
			r_in = current_cmd->parsed_cmd->r_in;
			while (r_in)
			{
				if (r_in->h_doc)
				{
					pipex->nb_h_doc++;
				}
				r_in = r_in->next;
			}
		}
		pipex->idx++;
		current_cmd = current_cmd->next;
	}
	if (pipex->nb_h_doc)
	{
		pipex->h_doc = 1;
		pipex->h_doc_name = malloc(sizeof(char *) * ((pipex->nb_h_doc) + 1));
		if (!pipex->h_doc_name)
			return ;
		pipex->h_doc_name[pipex->nb_h_doc++] = NULL;
	}
	pipex->idx = 0;
}

void	create_h_doc(t_command *parsed_cmd, t_pipex *pipex)
{
	t_command		*current_cmd;
	t_redir_in_2	*r_in;
	int				index;

	index = 0;
	current_cmd = parsed_cmd;
	while (pipex->idx < pipex->nb_cmd)
	{
		if (current_cmd->parsed_cmd->r_in)
		{
			r_in = current_cmd->parsed_cmd->r_in;
			while (r_in)
			{
				if (r_in->h_doc)
				{
					r_in->file = here_doc(r_in->file, pipex, index);
					index++;
				}
				r_in = r_in->next;
			}
		}
		pipex->idx++;
		current_cmd = current_cmd->next;
	}
	pipex->idx = 0;
}
