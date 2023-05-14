/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:27:14 by mrubina           #+#    #+#             */
/*   Updated: 2023/04/26 15:19:23 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	lim_as_flag(const char *s, int lim)
{
	if (ft_strchr(s, '.') && (lim == 0))
		return (-1);
	else
		return (lim);
}

static int	lim_variants(char conv, void **pp, int lim, int zeros)
{
	int	cnt;

	cnt = 0;
	if (lim != 0)
		cnt = add_pad(zeros, '0');
	else
	{
		if ((**(int **)pp == 0) && !s_c(conv))
		{
			free(*pp);
			*pp = 0;
		}
	}
	return (cnt);
}	

//prints padding and zeros for right alignment
int	right(const char *s, char conv, void **pp, int lim)
{
	int		cnt;
	int		sh_gr;
	int		zeros;
	int		padding;

	sh_gr = get_shift_group(s, conv, *pp);
	zeros = get_zeros(lim, get_width(*pp, conv, 1));
	lim = lim_as_flag(s, lim);
	padding = get_padding(s, conv, *pp, &lim);
	if (!ft_strchr(s, '.') && (get_al(s) == '0'))
	{	
		cnt = print_pref(sh_gr, *pp, conv);
		cnt = cnt + add_pad(padding, '0');
	}
	else if (!ft_strchr(s, '.') && (get_al(s) != '0'))
	{
		cnt = add_pad(padding, get_al(s)) + print_pref(sh_gr, *pp, conv);
	}
	else
	{
		cnt = add_pad(padding, ' ') + print_pref(sh_gr, *pp, conv);
		cnt = cnt + lim_variants(conv, pp, lim, zeros);
	}
	return (cnt);
}

//prints padding for left alignment
int	left(const char *s, char conv, void **pp, int lim)
{
	int	cnt;
	int	shift_group;
	int	zeros;
	int	width;
	int	min_width;

	cnt = 0;
	shift_group = get_shift_group(s, conv, *pp);
	min_width = get_min_width(s);
	width = get_width(*pp, conv, 1);
	zeros = get_zeros(lim, width);
	width = width_plus(width, shift_group, *pp);
	if ((!s_c(conv)) && (!ft_strchr(s, '.')))
		cnt = print_pref(shift_group, *pp, conv);
	else if (!s_c(conv) && ft_strchr(s, '.'))
	{
		cnt = print_pref(shift_group, *pp, conv);
		cnt = cnt + lim_variants(conv, pp, lim, zeros);
	}
	return (cnt);
}

//prints padding for text with right alignment
int	text(const char *s, char conv, void **pp, int lim)
{
	int	cnt;
	int	width;
	int	min_width;

	cnt = 0;
	min_width = get_min_width(s);
	width = get_width(*pp, conv, 1);
	if ((conv == 's') && (lim < (int)width) && (ft_strchr(s, '.')))
		cnt = add_pad(min_width - lim, get_al(s));
	else
		cnt = add_pad(min_width - width, get_al(s));
	return (cnt);
}
