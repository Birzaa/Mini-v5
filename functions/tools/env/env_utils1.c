#include "minishell.h"

void	print_env(t_env *env)
{
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
		free(tmp);
	}
}
