/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:27:14 by mrubina           #+#    #+#             */
/*   Updated: 2023/04/26 19:36:40 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//print padding
int	add_pad(int n, char c)
{
	int	i;

	i = 0;
	if (n > 0)
	{
		while (i < n)
		{
			int_putchar(c);
			i++;
		}
		return (n);
	}
	return (0);
}

//takes width wthout prefix and 
//gets width that includes prefix if it's possible for that type
int	width_plus(int width, int type, void *p_to_arg)
{
	int	w;

	w = 0;
	if ((type == 'n') && (p_to_arg == 0))
		w = width;
	else if ((type == 'n') && (*(int *)p_to_arg < 0))
		w = width + 1;
	else if ((type == '+') || (type == ' '))
		w = width + 1;
	else if (type == '#')
		w = width + 2;
	else
		w = width;
	return (w);
}

//get number of precision zeros
int	get_zeros(int lim, int width)
{
	int	zeros;

	if (lim > width)
		zeros = lim - width;
	else
		zeros = 0;
	return (zeros);
}

//printing prefix
int	print_pref(int type, void *p_to_arg, int conv_flag)
{	
	int	cnt;
	int	*arg;

	cnt = 0;
	if (p_to_arg == 0)
		return (0);
	arg = (int *)p_to_arg;
	if ((type == '#') && !((*arg == 0) && (conv_flag != 'p')))
		cnt = cnt + hexx(conv_flag);
	else if ((*arg >= 0) && (type == '+'))
		cnt = cnt + int_putchar('+');
	else if ((*arg >= 0) && (type == ' '))
		cnt = cnt + int_putchar(' ');
	else if ((*arg < 0) && ((type == 'n') || (type == '+') || (type == ' ')))
	{
		cnt = cnt + int_putchar('-');
		*arg = - (*arg);
	}
	return (cnt);
}
