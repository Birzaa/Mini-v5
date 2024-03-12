#include "minishell.h"

int	ft_one_c(char *s, char c)
{
	int	i;
	int	only;

	if (!s)
		return (0);
	only = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			only++;
		i++;
	}
	if (only == 1)
		return (1);
	return (0);
}

int	ft_more_than_one(char *s)
{
	int	more_q;
	int	more_dq;
	int	i;

	more_q = 0;
	more_dq = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			more_q++;
		else if (s[i] == '\"')
			more_dq++;
		i++;
	}
	if (more_dq > 1 || more_q > 1)
		return (1);
	return (0);
}

int	ft_more_c_pres(char *s, char c)
{
	int	i;
	int	more;

	i = 0;
	more = 0;
	while (s[i])
	{
		if (s[i] == c)
			more++;
		i++;
	}
	if (more > 1)
		return (1);
	return (0);
}

void	ft_putstr_fd_no_q(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			i++;
		else
		{
			if ((s[i + 1] == '\'' || s[i + 1] == '\"') && !s[i + 2])
				return ;
			write(fd, &s[i++], 1);
		}
	}
}

void	ft_putstr_fd_no_dq(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\"')
			i++;
		else
		{
			if ((s[i + 1] == '\'' || s[i + 1] == '\"') && !s[i + 2])
			{
				write(fd, &s[i++], 1);
				return ;
			}
			write(fd, &s[i++], 1);
		}
	}
}

void	ft_echo(char **content)
{
	int	i;
	int	check;

	i = 1;
	check = 0;
	if (!content[i])
		return (ft_putstr_fd("\n", 1));
	else if (!ft_strncmp(content[i], "-n", 3))
	{
		while (!ft_strncmp(content[i], "-n", 3))
		{
			if (ft_one_c(content[i + 1], '\'') || ft_one_c(content[i + 1],
					'\"'))
				i++;
			else
			{
				check = 1;
				i++;
			}
			if (!content[i])
				break ;
		}
	}
	while (content[i])
	{
		if (!ft_more_c_pres(content[i], '\''))
			ft_putstr_fd_no_q(content[i++], 1);
		else if (!ft_more_c_pres(content[i], '\"'))
			ft_putstr_fd_no_dq(content[i++], 1);
		else
			ft_putstr_fd(content[i++], 1);
		if (content[i])
			ft_putstr_fd(" ", 1);
	}
	if (!check)
		ft_putstr_fd("\n", 1);
}
