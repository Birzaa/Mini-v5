#include "minishell.h"

t_command	*ft_command_last(t_command *cmd)
{
	while (cmd)
	{
		if (!cmd->next)
			return (cmd);
		cmd = cmd->next;
	}
	return (cmd);
}

t_command	*ft_command_new(void)
{
	t_command	*elem;

	elem = malloc(sizeof(t_command));
	if (!elem)
		return (NULL);
	elem->next = NULL;
	return (elem);
}
void	add_back_cmd_out(t_command **cmd, t_command *new)
{
	t_command	*last;

	if (!*cmd)
		*cmd = new;
	else
	{
		last = ft_command_last(*cmd);
		last->next = new;
	}
}
