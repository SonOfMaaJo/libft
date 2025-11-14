/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:23:17 by vnaoussi          #+#    #+#             */
/*   Updated: 2025/11/13 14:10:28 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sjoin;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	sjoin = (char *)malloc(sizeof(char) * (len + 1));
	if(sjoin != NULL)
	{
		ft_strlcat(sjoin, s1, len + 1);
		ft_strlcat(sjoin, s2, len + 1);
	}
	return (sjoin);
}
