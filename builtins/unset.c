#include "minishell.h"

void	unset_with_equal(t_env *env, char *s)
{
	t_env	*previous;
	t_env	*target;
	int		len;

	len = ft_strlen(s);
	if (ft_envsize(env) == 1)
	{
		if (!ft_strncmp(env->content, s, len) && env->content[len] == '=')
			env->content = NULL;
		return ;
	}
	if (!ft_strncmp(env->content, s, len) && env->content[len] == '=')
		swap_content_env(env, env->next);
	previous = env;
	target = env->next;
	while (target)
	{
		if (!ft_strncmp(target->content, s, len) && target->content[len] == '=')
		{
			del_node_env(target, previous);
			break ;
		}
		previous = target;
		target = target->next;
	}
}

void	unset_without_equal(t_env *env, char *s)
{
	t_env	*previous;
	t_env	*target;
	int		len;

	len = ft_strlen(s);
	if (ft_envsize(env) == 1)
	{
		if (!ft_strncmp(env->content, s, len))
			env->content = NULL;
		return ;
	}
	if (!ft_strncmp(env->content, s, len))
		swap_content_env(env, env->next);
	previous = env;
	target = env->next;
	while (target)
	{
		if (!ft_strncmp(target->content, s, len))
		{
			del_node_env(target, previous);
			break ;
		}
		previous = target;
		target = target->next;
	}
}

// unset prend data->env et le nom d'une var env
void	unset(t_env *env, char *s)
{
	if (!ft_at_least_charset(s, "="))
		unset_without_equal(env, s);
	else
		unset_with_equal(env, s);
}
