#include "minishell.h"

void	free_multiple_env(t_env *env1, t_env *env2)
{
	free_env(env1);
	free_env(env2);
}
