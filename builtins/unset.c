#include "minishell.h"

// else if(!target->next) si le node a del est a la fin de env
// else si le node a del dans le milieu de env

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

void	unset(t_env *env, char *name)
{
	t_env	*previous;
	t_env	*target;
	int		len;

	// le cas du premier node de la list n'a pas l'air de marcher le reste a l'air okay
	// faudrait add front et try de des le premier pour voir si ca vien
	// du USER= ou juste du premier node de la list
	len = ft_strlen(name);
	if (!ft_strncmp(env->content, name, len) && env->content[len] == '=')
	{
		pop_node_env(env);
		return ;
	}
	previous = env;
	target = env->next;
	while (target)
	{
		if (!ft_strncmp(target->content, name, len)
			&& target->content[len] == '=')
		{
			del_node_env(target, previous);
			break ;
		}
		previous = target;
		target = target->next;
	}
}
