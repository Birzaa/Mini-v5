#include "minishell.h"

void	ft_exit(t_data *data)
{
	// free tout ce qu'il y a a free
	free_env(data->env);
	exit(0);
}
