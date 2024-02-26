#include "minishell.h"

/* export = add a var in env ; je l'add a la fin parce que c'est pratique
export sans	arg = write all env variables sorted with "export " at front
export avec	arg = add the var in env variables , check les cas d'erreur*/

// export prend &data->env et capart=bonjour
// export a fix, no arg, faut mettre les values entre ""

void	export_no_arg(t_env *env)
{
	t_env	*env_cpy;
	t_env	*tmp;

	tmp = NULL;
	env_cpy = NULL;
	refresh_env(env);
	while (env)
	{
		tmp = ft_env_new(env->content);
		if (!tmp)
		{
			free_multiple_env(env, env_cpy);
			return ;
		}
		add_back_env(&env_cpy, tmp);
		env = env->next;
	}
	env_cpy = ft_sort_env(env_cpy, ft_strcmp);
	print_env(env_cpy);
	tmp = env_cpy;
	print_env(tmp);
	while (env_cpy)
	{
		printf("export %s=\"%s\"\n", env_cpy->name, env_cpy->value);
		env_cpy = env_cpy->next;
	}
	free_env(tmp);
}

void	export(t_env **env, char *content)
{
	t_env	*tmp;

	tmp = ft_env_new(content);
	if (!tmp)
		return ;
	add_back_env(env, tmp);
}
