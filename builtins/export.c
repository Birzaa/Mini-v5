#include "minishell.h"

/* export = add a var in env ; je l'add a la fin parce que c'est pratique
export sans	arg = write all env variables sorted with "export " at front
export avec	arg = add the var in env variables , check les cas d'erreur*/

// export prend &data->env et capart=bonjour
// export a fix, no arg, faut mettre les values entre ""

void	export_new_add_back(t_env **env, t_env *tmp, char *cmd)
{
	tmp = ft_env_new(cmd);
	if (!tmp)
		return (perror(""));
	add_back_env(env, tmp);
	return ;
}

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
			return (perror(""), free_multiple_env(env, env_cpy));
		add_back_env(&env_cpy, tmp);
		env = env->next;
	}
	env_cpy = ft_sort_env(env_cpy, ft_strcmp);
	tmp = env_cpy;
	while (tmp)
	{
		print_export(tmp->content);
		tmp = tmp->next;
	}
	free_env(env_cpy);
}

void	export(t_env **env, char **cmd)
{
	t_env	*tmp;

	tmp = NULL;
	if (!cmd[1])
		return (export_no_arg((*env)));
	else if (!ft_strncmp("_", cmd[1], 2) || !ft_strncmp("_=", cmd[1], 2))
		return ;
	else if (ft_export_checking(cmd[1]))
	{
		printf("bash: export: `%s': not a valid identifier\n", cmd[1]);
		// 	g_ret_value = 1;
		return ;
	}
	else if (ft_at_least_charset(cmd[1], "=") && !export_exist((*env), cmd[1]))
		export_new_add_back(env, tmp, cmd[1]);
	else if (!ft_at_least_charset(cmd[1], "=") && !exp_exist_bis((*env),
			cmd[1]))
		export_new_add_back(env, tmp, cmd[1]);
	else
		replace_export(env, cmd[1]);
}
