/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 23:39:34 by vnaoussi          #+#    #+#             */
/*   Updated: 2025/11/16 01:01:00 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	getlenword(char const *s, char c)
{
	int		n;
	int		i;

	n = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i++] != '\0')
			n++;
		while (s[i] != c && s[i])
			i++;
	}
	return (n);
}
static char	*getnextword(char const *s, char c)
{
	int		i;

	i = 0;
	while (s[i] == c)
		i++;
	return ((char *)s + i);
}

static int getlentword(char const *s, char c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**ft_free(char **splitw)
{
	int		i;

	i = 0;
	while (splitw[i] != NULL)
		free(splitw[i++]);
	free(splitw);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		len;
	int		lenw;
	int		i;
	char	*pos;
	char	**splitw;

	i = 0;
	len = getlenword(s, c);
	lenw = 0;
	pos = getnextword(s, c);
	splitw = (char **)malloc(sizeof(char *) * (len + 1));
	if (splitw != NULL)
	{
		while (i < len)
		{
			lenw = getlentword(pos, c);
			splitw[i] = (char *)malloc(sizeof(char) * (lenw + 1));
			if (splitw[i] != NULL)
				ft_strlcpy(splitw[i], pos, lenw + 1);
			else
				return (ft_free(splitw));
			pos = getnextword(pos + lenw + 1, c);
			i++;
		}
		splitw[i] = NULL;
	}
	return (splitw);

}
