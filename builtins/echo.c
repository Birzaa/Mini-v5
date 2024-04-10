/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:43:21 by abougrai          #+#    #+#             */
/*   Updated: 2024/04/10 13:24:41 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_flag(char *str)
{
	int	i;
	int	check_dash;
	int	check_n;

	i = 1;
	check_dash = 0;
	check_n = 0;
	if (str[0] == '-')
		check_dash++;
	else
		return (1);
	while (str[i])
	{
		if (str[i] != 'n' && check_dash)
			return (1);
		i++;
	}
	return (0);
}

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
	while (!ft_strncmp(content[i], "-n", 3) || !ft_check_flag(content[i]))
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
