#include "minishell.h"

// free tout ce qu'il y a a free
void	ft_exit(t_data *data)
{
	free_env(data->env);
	exit(0);
}
