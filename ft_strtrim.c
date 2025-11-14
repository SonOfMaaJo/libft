/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 14:14:25 by vnaoussi          #+#    #+#             */
/*   Updated: 2025/11/14 14:43:03 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t ft_nbchstr(char const *s1, char const *set)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = 0;
	while (s1[i++])
		if (ft_strchr(set, s1[i - 1]) != NULL)
			nb++;
	return (nb);
}

char 	*ft_strtrim(char const *s1, char const *set)
{
	char	*strtrim;
	size_t	trim_len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	trim_len = ft_strlen(s1) - ft_nbchstr(s1, set);
	strtrim = (char *)malloc(sizeof(char) * (trim_len + 1));
	if (strtrim != NULL)
	{
		while (s1[i++])
			if (ft_strchr(set, s1[i - 1]) == NULL)
				strtrim[j++] = s1[i - 1];
		strtrim[j] = '\0';
	}
	return (strtrim);
}
