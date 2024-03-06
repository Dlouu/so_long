/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_arg_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:30:45 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/01/25 18:16:12 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_printf.h"

void	pf_arg_char(char c, t_ret *ret)
{
	int	temp;

	temp = ft_putchar(c);
	if (temp == -1)
		ret->error = 1;
	ret->written += temp;
}
