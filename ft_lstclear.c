/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 02:16:59 by vnaoussi          #+#    #+#             */
/*   Updated: 2025/11/16 02:26:28 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*element;

	element = *lst;
	while (element->next != NULL)
	{
		*lst = element->next;
		ft_lstdelone(element, del);
		element = *lst;
	}
	ft_lstdelone(element, del);
	*lst = NULL;
}
