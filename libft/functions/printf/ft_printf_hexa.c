/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:26:42 by thenwood          #+#    #+#             */
/*   Updated: 2023/12/07 13:07:35 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_put_in_hexa(unsigned int n, char format)
{
	if (n >= 16)
	{
		ft_put_in_hexa(n / 16, format);
		ft_put_in_hexa(n % 16, format);
	}
	else
	{
		if (n <= 9)
		{
			ft_putchar(n + '0');
		}
		else
		{
			if (format == 'x')
				ft_putchar(n - 10 + 'a');
			else
				ft_putchar(n - 10 + 'A');
		}
	}
}

int	ft_base_len_hexa(unsigned int n)
{
	int	len;

	len = 0;
	while (n)
	{
		n /= 16;
		len++;
	}
	return (len);
}

int	ft_manage_base_hexa(unsigned int n, char format)
{
	int	len;

	ft_put_in_hexa(n, format);
	if (n == 0)
		return (1);
	len = ft_base_len_hexa(n);
	return (len);
}
