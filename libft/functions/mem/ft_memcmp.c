/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:51:30 by thenwood          #+#    #+#             */
/*   Updated: 2023/12/12 20:59:40 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*str_1;
	unsigned const char	*str_2;

	str_1 = (unsigned const char *)s1;
	str_2 = (unsigned const char *)s2;
	if (!n)
		return (0);
	if (n == 0)
		return (0);
	while (n)
	{
		if (*str_1 != *str_2)
			return (*str_1 - *str_2);
		str_1++;
		str_2++;
		n--;
	}
	return (0);
}
