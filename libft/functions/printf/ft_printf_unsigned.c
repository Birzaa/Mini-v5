/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:59:35 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/18 18:14:00 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_itoa_pf(unsigned int n, int len)
{
	char	*tab;

	tab = malloc(sizeof(char) * len + 1);
	if (!tab)
		return (0);
	tab[len] = '\0';
	while (n)
	{
		tab[len - 1] = n % 10 + '0';
		n /= 10;
		len--;
	}
	return (tab);
}

int	ft_base_len_unsigned(unsigned int n)
{
	int	len;

	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_manage_unsigned(unsigned int n)
{
	char	*result;
	int		len;

	len = 0;
	if (n == 0)
		return (ft_putchar('0'));
	result = (ft_itoa_pf(n, ft_base_len_unsigned(n)));
	len += ft_putstr(result);
	free(result);
	return (len);
}
