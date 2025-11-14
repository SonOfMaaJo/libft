/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 01:14:45 by vnaoussi          #+#    #+#             */
/*   Updated: 2025/11/11 02:07:35 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	if_overlap(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 1;
	while (i < n)
		if (src + i++ == dest)
			return (i - 1);
	return (0);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	size_t	end_f;

	end_f = if_overlap(dest, src, n);
	if (end_f > 0)
	{
		i = end_f;
		while (i < n)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
		}
	}
	else
		end_f = n;
	i = 0;
	while (i < end_f)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}
