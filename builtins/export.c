#include "minishell.h"

/* export = add a var in env ; je l'add a la fin parce que c'est pratique
export sans	arg = write all env variables sorted with "export " at front
export avec	arg = add the var in env variables , check les cas d'erreur*/

// export prend &data->env et capart=bonjour

// export a fix, no arg, faut mettre les values entre ""
// si created export, export no arg devient "declare -x" et meme chose
//
void	export_no_arg(t_env *env)
{
	t_env	*env_cpy;
	t_env	*tmp;

	tmp = NULL;
	env_cpy = NULL;
	refresh_env(env);
	while (env)
	{
		tmp = ft_env_new(env->content, env->created);
		if (!tmp)
		{
			free_multiple_env(env, env_cpy);
			return ;
		}
		add_back_env(&env_cpy, tmp);
		env = env->next;
	}
	env_cpy = ft_sort_env(env_cpy, ft_strcmp);
	tmp = env_cpy;
	while (tmp)
	{
		printf("export %s=\"%s\"\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	free_env(env_cpy);
}

void	export(t_env **env, char *content)
{
	t_env	*tmp;

	tmp = ft_env_new(content, (*env)->created);
	if (!tmp)
		return ;
	add_back_env(env, tmp);
}
