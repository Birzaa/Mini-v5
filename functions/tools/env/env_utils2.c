#include "minishell.h"

t_env	*ft_sort_env(t_env *env, int (*cmp)(char *, char *))
{
	char	*str;
	t_env	*tmp;

	tmp = env;
	while (env->next)
	{
		if (((*cmp)(env->content, env->next->content)) >= 0)
		{
			str = env->content;
			env->content = env->next->content;
			env->next->content = str;
			env = tmp;
		}
		else
			env = env->next;
	}
	env = tmp;
	return (env);
}

int	ft_envsize(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

void	del_node_env(t_env *target, t_env *previous)
{
	if (!target->next)
	{
		previous->next = NULL;
		free(target);
	}
	else
	{
		previous->next = target->next;
		free(target);
	}
}

void	swap_content_env(t_env *node1, t_env *node2)
{
	char	*tmp;

	tmp = node1->content;
	node1->content = node2->content;
	node2->content = tmp;
}

void	pop_node_env(t_env *env)
{
	t_env	*tmp;

	if (env)
	{
		tmp = env;
		env = env->next;
		free(tmp);
	}
}
