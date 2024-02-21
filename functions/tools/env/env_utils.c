#include "minishell.h"

void	print_env(t_env *env)
{
	while (env)
	{
		printf("%s\n", env->content);
		env = env->next;
	}
}

t_env	*ft_envlast(t_env *env)
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
	t_env	*el;

	el = malloc(sizeof(*el));
	if (!el)
		return (NULL);
	el->content = content;
	el->next = NULL;
	return (el);
}

void	ft_env_add_back(t_env **env, t_env *new)
{
	t_env	*last;

	if (!*env)
		*env = new;
	else
	{
		last = ft_envlast(*env);
		last->next = new;
	}
	return ;
}
