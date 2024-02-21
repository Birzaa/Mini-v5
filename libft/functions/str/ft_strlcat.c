/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:11:42 by thenwood          #+#    #+#             */
/*   Updated: 2023/12/12 20:57:33 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	srclen;
	size_t	dstlen;

	if (!dst && !size)
		return (0);
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	i = ft_strlen(dst);
	j = 0;
	if (size == 0)
		return (srclen);
	if (size < dstlen)
		return (size + srclen);
	else
	{
		while (src[j] && (dstlen + j) < size)
			dst[i++] = src[j++];
		if ((dstlen + j) == size && dstlen < size)
			dst[--i] = '\0';
		else
			dst[i] = '\0';
		return (dstlen + srclen);
	}
}
