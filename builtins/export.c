#include "minishell.h"

/* export = add a var in env ; je l'add a la fin parce que c'est pratique
export sans	arg = write all env variables sorted with "export " at front
export avec	arg = add the var in env variables , check les cas d'erreur*/

// export prend &data->env et capart=bonjour
// export a fix, no arg, faut mettre les values entre ""

void	replace_export(t_env **env, char *content)
{
	t_env	*tmp;
	int len_c = ft_strlen(content);
	(void)len_c;
	(void)tmp;
	tmp = (*env);
	/* while (ft_strncmp())
	{
		tmp = tmp->next;
	} */

}

int	check_export_exit(t_env *env, char *content)
{
	t_env	*tmp;
	int		len_c;

	len_c = ft_strlen(content);
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, content, len_c))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	print_export(char *content)
{
	int	i;

	i = 0;
	while (content[i] != '=')
		write(1, &content[i++], 1);
	write(1, &content[i++], 1);
	write(1, "\"", 1);
	while (content[i])
		write(1, &content[i++], 1);
	write(1, "\"\n", 2);
}

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
	tmp = env_cpy;
	while (tmp)
	{
		print_export(tmp->content);
		tmp = tmp->next;
	}
	free_env(env_cpy);
}

void	export(t_env **env, char *content)
{
	t_env	*tmp;

	// check if variable already exist if yes just return
	/* if (!check_export_exit((*env), content))
	{
		} */
		tmp = ft_env_new(content);
		if (!tmp)
			return ;
		add_back_env(env, tmp);
		print_env((*env));
		return ;
	
	/* else
		replace_export(env, content); */
}
