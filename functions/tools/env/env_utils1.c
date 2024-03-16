#include "minishell.h"

void	print_env(t_env *env)
{
	refresh_env(env, 0);
	if (!env->content && !env->next)
		return ;
	while (env)
	{
		if (!ft_strncmp(env->content, "PWD", 3))
			print_pwd_env();
		else if (!ft_at_least_charset(env->content, "="))
			ft_nothing();
		else
		{
			ft_putstr_fd(env->content, 1);
			ft_putchar_fd('\n', 1);
		}
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

	elem = malloc(sizeof(t_env));
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
