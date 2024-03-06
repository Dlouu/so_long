/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_arg_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:30:45 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/01/25 18:16:12 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_printf.h"

void	pf_arg_str(char *s, t_ret *ret)
{
	int	temp;

	if (s == NULL)
		s = "(null)";
	temp = ft_putstr(s);
	if (temp == -1)
		ret->error = 1;
	ret->written += temp;
}
