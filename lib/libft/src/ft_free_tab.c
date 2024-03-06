/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:50:26 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/02/29 13:08:21 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

void	ft_free_tab(char **tab, int height)
{
	int	i;

	i = 0;
	while (height > i)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
