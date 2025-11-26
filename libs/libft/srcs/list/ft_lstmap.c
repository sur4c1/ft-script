/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:55:32 by bguyot            #+#    #+#             */
/*   Updated: 2024/11/21 05:52:09 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	**res;
	t_list	*tmp;

	res = malloc(sizeof (t_list *));
	if (!res)
		return (NULL);
	while (lst)
	{
		tmp = ft_lstnew(f(lst->content));
		ft_lstadd_back(res, tmp);
		ft_lstdelone(tmp, del);
		lst = lst->next;
	}
	return (*res);
}
