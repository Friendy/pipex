/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:27:14 by mrubina           #+#    #+#             */
/*   Updated: 2023/04/26 15:15:27 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//width of unsigned number
static int	u_width(unsigned int u)
{
	char	*s;
	int		w;

	if (u > 2147483647)
	{
		s = ft_itoa(u / 10);
		w = ft_strlen(s) + 1;
	}
	else
	{
		s = ft_itoa(u);
		w = ft_strlen(s);
	}
	free(s);
	return (w);
}

//width of integer
static int	i_width(int i)
{
	char	*s;
	int		w;

	s = ft_itoa(i);
	w = ft_strlen(s);
	free(s);
	return (w);
}

//width of hex number
static int	hex_width(unsigned long n)
{
	int	cnt;

	cnt = 0;
	if (n == 0)
		cnt = 1;
	else
	{
		while (n > 0)
		{
			n = n / 16;
			cnt++;
		}
	}
	return (cnt);
}

//takes width with prefix and returns width without prefix for bonus
static int	width_bonus(void *s, char conv_flag, char bonus, int width)
{
	if ((conv_flag == 'p') && (bonus == 1))
		width = width - 2;
	else if (d_i(conv_flag) && (bonus == 1) && (*((int *)s) < 0))
		width = width - 1;
	return (width);
}

//width of any argument
//for bonus it's without prefix
int	get_width(void *s, char conv_flag, char bonus)
{
	int	width;

	width = 0;
	if (s == 0)
		return (width);
	if (conv_flag == 'c')
		width = 1;
	else if (conv_flag == 's')
		width = ft_strlen(s);
	else if (conv_flag == 'p')
	{
		width = hex_width(*(unsigned long *)s) + 2;
		width = width_bonus(s, conv_flag, bonus, width);
	}
	else if ((conv_flag == 'd') || (conv_flag == 'i'))
	{
		width = i_width(*((int *)s));
		width = width_bonus(s, conv_flag, bonus, width);
	}
	else if (conv_flag == 'u')
		width = u_width(*(unsigned int *)s);
	else if (x_x(conv_flag))
		width = hex_width(*(unsigned int *)s);
	return (width);
}
