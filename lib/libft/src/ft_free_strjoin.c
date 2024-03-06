/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strjoin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:07:50 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/02/29 13:08:10 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

char	*ft_free_strjoin(char *s1, char *s2)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	if (!new_str)
	{
		free(s1);
		return (NULL);
	}
	free(s1);
	return (new_str);
}
