#include "minishell.h"

int	ft_contain_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_at_least_charset(char *str, char *charset)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_contain_charset(str[i], charset))
			return (1);
		i++;
	}
	return (0);
}
