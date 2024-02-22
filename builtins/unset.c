#include "minishell.h"

void	unset(t_env *env, char *s)
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
