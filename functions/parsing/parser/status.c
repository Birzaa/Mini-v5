#include "minishell.h"

void	parsing_status(t_stack *list)
{
	t_node	*node;
	int		i;

	i = 0;
	node = list->head;
	while (i < list->size)
	{
		if (node->type == ENV)
		{
			if (ft_strncmp(node->next->content, "?", 1) == 0)
			{
				printf("ww: %s\n", node->next->content);
				node->type = WHITE_SPACE;
				node->next->type = WORD;
				char *r = "55829651";
				node->next->content = r;
				node->next->len = ft_strlen(r);
			}
		}
		node = node->next;
		i++;
	}
}
