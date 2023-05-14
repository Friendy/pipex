/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcuts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:27:14 by mrubina           #+#    #+#             */
/*   Updated: 2023/04/26 19:36:45 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	s_c(int conv_flag)
{
	return ((conv_flag == 's') || (conv_flag == 'c'));
}

int	x_x(int conv_flag)
{
	return ((conv_flag == 'x') || (conv_flag == 'X'));
}

int	d_i(int conv_flag)
{
	return ((conv_flag == 'd') || (conv_flag == 'i'));
}

int	xx_nz(int conv_flag, void *p_to_arg)
{
	if (p_to_arg != 0)
		return ((x_x(conv_flag)) && (*(unsigned int *)p_to_arg != 0));
	else
		return (0);
}
