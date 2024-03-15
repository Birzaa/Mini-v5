#include "minishell.h"

void	ft_env(t_data *data, char **content)
{
	if (!content[1])
		print_env(data->env);
	else if (content[1])
		ft_printf("env: ’%s’: No such file or directory\n", content[1]);
	/* 	else if (content[1] && content[1][0] == '')
			ft_printf("env: ’%s’: No such file or directory", content[1]); */
}
