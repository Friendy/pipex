/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:27:14 by mrubina           #+#    #+#             */
/*   Updated: 2023/04/26 15:19:31 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//determine shift group
int	get_shift_group(const char *s, char conv, void *p_arg)
{
	if (s_c(conv))
		return ('t');
	else if (conv == 'u')
		return ('u');
	else if ((ft_strchr(s, '#') && xx_nz(conv, p_arg)) || (conv == 'p'))
		return ('#');
	else if (ft_strchr(s, '+') && (d_i(conv)))
		return ('+');
	else if (ft_strchr(s, ' ') && (d_i(conv)))
		return (' ');
	else if (x_x(conv))
		return ('x');
	else
		return ('n');
}

/* 
character limit
if a period does not exist limit equals width
if a period exists and limit equals zero we have a special case
*/
int	get_lim(const char *s, int width, int conv)
{
	int		lim;
	char	*lim_start;

	lim = 0;
	lim_start = ft_strchr(s, '.');
	if (lim_start)
	{
		lim = ft_atoi(lim_start + 1);
		if ((conv == 's') && (lim > width))
			lim = width;
		else if (!s_c(conv) && (lim == 0))
			lim = -1;
	}	
	else
		lim = width;
	return (lim);
}

//calculate final padding
static int	calc_padding(int zeros, int min_width, int width)
{
	int	padding;

	if (min_width > width + zeros)
		padding = min_width - width - zeros;
	else
		padding = 0;
	return (padding);
}

/* 
we handle the case with zero argument and zero limit
*/
int	get_padding(const char *s, char conv, void *p_arg, int *p_lim)
{
	int	min_width;
	int	shift_group;
	int	zeros;
	int	padding;
	int	width;

	if (!s_c(conv) && (p_arg != 0) && (*(int *)p_arg == 0) && (*p_lim == -1))
		p_arg = 0;
	width = get_width(p_arg, conv, 1);
	*p_lim = get_lim(s, width, conv);
	if (*p_lim == -1)
		*p_lim = 0;
	min_width = get_min_width(s);
	shift_group = get_shift_group(s, conv, p_arg);
	zeros = get_zeros(*p_lim, width);
	if (!s_c(conv))
		width = width_plus(width, shift_group, p_arg);
	if (s_c(conv))
		padding = calc_padding(0, min_width, width);
	else
		padding = calc_padding(zeros, min_width, width);
	return (padding);
}
