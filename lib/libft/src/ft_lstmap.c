/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:47:51 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/01/25 18:16:12 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;
	void	*f_temp;

	if (!lst || !f || !del)
		return (NULL);
	new = NULL;
	while (lst)
	{
		f_temp = (*f)(lst->content);
		temp = ft_lstnew(f_temp);
		if (!temp)
		{
			ft_lstclear(&new, (*del));
			del(f_temp);
			return (NULL);
		}
		ft_lstadd_back(&new, temp);
		lst = lst->next;
	}
	return (new);
}
