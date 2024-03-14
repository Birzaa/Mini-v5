#include "minishell.h"

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
		ft_putstr_fd(content[i++], 1);
		if (content[i])
			ft_putstr_fd(" ", 1);
	}
	if (!check)
		ft_putstr_fd("\n", 1);
}
