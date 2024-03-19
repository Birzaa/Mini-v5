#include "minishell.h"

int	ft_check_symbol(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (!ft_isalnum(content[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_get_symbol_join(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (!ft_isalpha(content[i]))
			return (&content[i]);
		i++;
	}
	return (NULL);
}

char	*ft_get_symbol_expand(char *content)
{
	char	*expand;
	int		i;

	i = 0;
	expand = ft_calloc(1, ft_strlen_symbol(content) + 2);
	if (!expand)
		return (NULL);
	while (content[i])
	{
		if (!ft_isalpha(content[i]))
		{
			expand[i + 1] = '\0';
			return (expand);
		}
		expand[i] = content[i];
		i++;
	}
	return (NULL);
}

int	ft_strlen_symbol(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
			return (i);
		i++;
	}
	return (i);
}
