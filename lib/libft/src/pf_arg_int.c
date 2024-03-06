/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_arg_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:30:45 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/01/25 18:16:12 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_printf.h"

void	pf_arg_int(long long int n, t_ret *ret)
{
	int	temp;

	temp = ft_nlen_base(n, 10);
	if (temp != ft_putnbr_base(n, "0123456789"))
		ret->error = 1;
	ret->written += temp;
}
