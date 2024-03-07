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
	refresh_env(env, 0);
	while (env)
	{
		tmp = ft_env_new(env->content);
		if (!tmp)
			return (free_multiple_env(env, env_cpy)) ;
		add_back_env(&env_cpy, tmp);
		env = env->next;
	}
	env_cpy = ft_sort_env(env_cpy, ft_strcmp);
	tmp = env_cpy;
	while (tmp->next)
	{
		print_export(tmp->content);
		tmp = tmp->next;
	}
	free_env(env_cpy);
}

void	export(t_env **env, char *content)
{
	t_env	*tmp;

	/* 	if content est ne chaine de char vide
		{
			ft_putstr_fd("bash: export: `': not a valid identifier", 1);
			//g_ret_value = 1;
			return ;
		} */
	if (ft_export_checking(content))
	{
		printf("bash: export: `%s': not a valid identifier\n", content);
		// 		g_ret_value = 1;
		return ;
	}
	if (!check_export_exist((*env), content))
	{
		tmp = ft_env_new(content);
		if (!tmp)
			return ;
		add_back_env(env, tmp);
		return ;
	}
	else
		replace_export(env, content);
}
