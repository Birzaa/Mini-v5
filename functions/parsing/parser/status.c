#include "minishell.h"

int	ft_strstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!big && !len)
		return (0);
	i = 0;
	if (little[i] == '\0')
		return (0);
	while (big[i])
	{
		j = 0;
		while (big[i + j] == little[j] && i < len)
		{
			if (little[j + 1] == '\0' && j + 1 == ft_strlen(little) && (i
					+ j) < len)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

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
