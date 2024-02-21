/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:27:52 by thenwood          #+#    #+#             */
/*   Updated: 2023/12/07 13:07:27 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_len_base(int n)
{
	long	nb;
	int		len;

	len = 0;
	if (n < 0)
	{
		nb = -n;
		len++;
	}
	else
		nb = n;
	while (nb != 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

void	ft_putnbr(int n)
{
	long int	nb;

	nb = n;
	if (n < 0)
	{
		nb *= -1;
		ft_putchar('-');
	}
	if (nb >= 10)
		ft_putnbr(nb / 10);
	ft_putchar(nb % 10 + '0');
}

int	ft_manage_base(int n)
{
	int	len;

	len = 0;
	len = ft_len_base(n);
	if (len == 0)
		len++;
	ft_putnbr(n);
	return (len);
}
