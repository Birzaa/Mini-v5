#include "minishell.h"

void	ft_echo(char **content)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (!content[i])
		return (ft_putstr_fd("\n", 1));
	while (!ft_strncmp(content[i], "-n", 3))
	{
		flag = 1;
		i++;
		if (!content[i])
			break ;
	}
	while (content[i])
	{
		ft_putstr_fd(content[i++], 1);
		if (content[i])
			ft_putstr_fd(" ", 1);
	}
	if (!flag)
		ft_putstr_fd("\n", 1);
	// g_ret_value = 0;
}
