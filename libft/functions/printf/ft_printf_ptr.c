/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:24:52 by thenwood          #+#    #+#             */
/*   Updated: 2023/12/07 13:07:41 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_len_base_ptr(unsigned long long n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		n /= 16;
		len++;
	}
	return (len);
}

void	ft_put_in_hexa_ptr(unsigned long long n)
{
	if (n >= 16)
	{
		ft_put_in_hexa_ptr(n / 16);
		ft_put_in_hexa_ptr(n % 16);
	}
	else
	{
		if (n <= 9)
			ft_putchar(n + '0');
		else
			ft_putchar(n - 10 + 'a');
	}
}

int	ft_manage_address(unsigned long long ptr)
{
	int	len;

	len = 0;
	if (!ptr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	len += ft_putstr("0x");
	len += ft_len_base_ptr(ptr);
	ft_put_in_hexa_ptr(ptr);
	return (len);
}
