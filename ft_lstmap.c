/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 02:35:30 by vnaoussi          #+#    #+#             */
/*   Updated: 2025/11/16 03:02:13 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nlist;
	t_list	*result;

	if (lst == NULL)
		return (NULL);
	nlist = (t_list *)malloc(sizeof(t_list));
	result = nlist;
	if (nlist != NULL)
	{
		while (lst != NULL)
		{
			nlist->content = f(lst->content);
			if (lst->next == NULL)
			{
				nlist->next = NULL;
				return (result);
			}
			nlist->next = (t_list *)malloc(sizeof(t_list));
			if (nlist->next == NULL)
				ft_lstclear(&result, del);
			nlist = nlist->next;
			lst = lst->next;
		}
	}
	return (result);
}
