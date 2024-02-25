#include "minishell.h"

void	print_env(t_env *env)
{
	refresh_env(env);
	if (!env->content && !env->next)
		return ;
	while (env)
	{
		printf("%s\n", env->content);
		env = env->next;
	}
}

t_env	*ft_env_last(t_env *env)
{
	while (env)
	{
		if (!env->next)
			return (env);
		env = env->next;
	}
	return (env);
}

t_env	*ft_env_new(void *content)
{
	t_env	*elem;

	elem = malloc(sizeof(*elem));
	if (!elem)
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	elem->name = ft_get_name_env(content);
	if (!elem->name)
		return (NULL);
	elem->value = ft_get_value_env(content);
	if (!elem->value)
		return (NULL);
	return (elem);
}

void	add_back_env(t_env **env, t_env *new)
{
	t_env	*last;

	if (!*env)
		*env = new;
	else
	{
		last = ft_env_last(*env);
		last->next = new;
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	tmp = NULL;
	if (!env)
		return ;
	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}
