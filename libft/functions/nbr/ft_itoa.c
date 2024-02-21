/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:19:12 by thenwood          #+#    #+#             */
/*   Updated: 2024/01/11 21:30:16 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_get_size(int n)
{
	long	nb;
	int		size;

	size = 0;
	if (n < 0)
	{
		nb = -n;
		size++;
	}
	else
		nb = n;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int		size;
	int		i;
	char	*result;
	long	temp;

	size = ft_get_size(n);
	result = malloc(sizeof(char) * size + 1);
	if (!result)
		return (NULL);
	temp = n;
	if (n < 0)
		temp = -temp;
	i = 1;
	if (temp == 0)
		result[0] = '0';
	while (temp)
	{
		result[size - i++] = (temp % 10) + '0';
		temp /= 10;
	}
	if (n < 0)
		result[0] = '-';
	result[size] = '\0';
	return (result);
}
