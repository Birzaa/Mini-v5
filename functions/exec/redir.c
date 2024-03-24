/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:04:14 by thomas            #+#    #+#             */
/*   Updated: 2024/03/24 15:10:51 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*here_doc(char *av, t_pipex *pipex, int index)
{
	int		file;
	char	*buf;
	char	*name_file;

	name_file = ft_strjoin(av, ft_itoa(index));
	pipex->h_doc_name[index] = malloc(ft_strlen(name_file) + 1);
	if (!pipex->h_doc_name[index])
	{
		ft_free_tab(pipex->h_doc_name);
		return (NULL);
	}
	pipex->h_doc_name[index] = name_file;
	file = open(name_file, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
	{
		printf("FLOP");
		free(name_file);
		return (NULL);
		// MSG ERREUR
	}
	while (1)
	{
		write(1, "\033[1;34m~> \033[0m", 15);
		buf = get_next_line(0);
		if (!buf)
			exit(1);
		if (!ft_strcmp(av, buf))
			break ;
		write(file, buf, ft_strlen(buf));
		write(file, "\n", 1);
		free(buf);
	}
	free(buf);
	close(file);
	return (name_file);
}

void	open_redir_in(t_command *head, t_pipex *pipex)
{
	pipex->infile = pipex->saved_in;
	while (head->parsed_cmd->r_in)
	{
		if (!head->parsed_cmd->r_in->h_doc)
			pipex->infile = open(head->parsed_cmd->r_in->file, O_RDONLY, 0644);
		else
		{
			pipex->h_doc = 1;
			pipex->infile = open(head->parsed_cmd->r_in->file, O_RDONLY, 0644);
		}
		if (pipex->infile == -1)
		{
			printf("Impossible de in\n");
			exit(1);
		}
		head->parsed_cmd->r_in = head->parsed_cmd->r_in->next;
	}
}

void	open_redir_out(t_command *head, t_pipex *pipex)
{
	pipex->outfile = pipex->saved_out;
	while (head->parsed_cmd->r_out)
	{
		if (!head->parsed_cmd->r_out->append)
			pipex->outfile = open(head->parsed_cmd->r_out->file,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			pipex->outfile = open(head->parsed_cmd->r_out->file,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (pipex->outfile == -1)
		{
			printf("Impossible de out\n");
			exit(1);
		}
		head->parsed_cmd->r_out = head->parsed_cmd->r_out->next;
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
		pipex->h_doc_name = malloc(sizeof(char *) * pipex->nb_h_doc + 1);
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
