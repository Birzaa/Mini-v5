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
