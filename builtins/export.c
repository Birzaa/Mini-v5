#include "minishell.h"

/* export = add a var in env ; je l'add a la fin parce que c'est pratique
export sans	arg = write all env variables sorted with "export " at front
export avec	arg = add the var in env variables , check les cas d'erreur*/

// export prend &data->env et capart=bonjour
void	export_no_arg(t_env *env)
{
	env = ft_sort_env(env, ft_strcmp);
	while (env)
	{
		printf("export %s\n", env->content);
		env = env->next;
	}
}

void	export(t_env **env, char *content)
{
	t_env	*tmp;

	tmp = ft_env_new(content);
	if (!tmp)
		return ;
	ft_env_add_back(env, tmp);
}
