/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:43:21 by abougrai          #+#    #+#             */
/*   Updated: 2024/04/01 08:30:51 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_content(char **content, int fd, int *i)
{
	ft_putstr_fd(content[(*i)++], fd);
	if (content[(*i)])
		ft_putstr_fd(" ", fd);
}

void	ft_echo(char **content, t_pipex *p)
{
	int	i;
	int	flag;
	int	fd;

	(void)p;
	i = 1;
	flag = 0;
	if (p->fd_echo == 1)
		fd = p->outfile;
	else
		fd = 1;
	if (!content[i])
		return (ft_putstr_fd("\n", fd));
	while (!ft_strncmp(content[i], "-n", 3))
	{
		flag = 1;
		i++;
		if (!content[i])
			break ;
	}
	while (content[i])
		print_content(content, fd, &i);
	if (!flag)
		ft_putstr_fd("\n", fd);
	g_sig.status = 0;
}
