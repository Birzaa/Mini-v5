/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:09:41 by thenwood          #+#    #+#             */
/*   Updated: 2023/12/07 13:07:51 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_valid_format(const char c)
{
	if (c == 'c' || c == 's' || c == 'x' || c == 'X' || c == '%' || c == 'i'
		|| c == 'd' || c == 'u' || c == 'p')
		return (1);
	return (0);
}

int	ft_write_correct_format(va_list ap, char format)
{
	int	i;

	i = 0;
	if (format == 'c')
		i = ft_putchar(va_arg(ap, int));
	else if (format == 's')
		i = ft_putstr(va_arg(ap, char *));
	else if (format == 'i' || format == 'd')
		i = ft_manage_base(va_arg(ap, int));
	else if (format == 'x' || format == 'X')
		i = ft_manage_base_hexa(va_arg(ap, unsigned int), format);
	else if (format == 'u')
		i = ft_manage_unsigned(va_arg(ap, unsigned int));
	else if (format == '%')
		i = ft_putchar('%');
	else if (format == 'p')
		i = ft_manage_address(va_arg(ap, unsigned long long));
	return (i);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		len;

	len = 0;
	i = 0;
	if (!str || *str == '\0')
		return (0);
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (ft_valid_format(str[i + 1]))
			{
				len += ft_write_correct_format(ap, str[i + 1]);
				i += 2;
			}
		}
		else
			len += ft_putchar(str[i++]);
	}
	va_end(ap);
	return (len);
}
