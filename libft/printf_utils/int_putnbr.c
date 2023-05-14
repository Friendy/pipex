/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_putnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:36:21 by mrubina           #+#    #+#             */
/*   Updated: 2023/04/26 19:36:48 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long	power(int n, int unsigned p)
{
	int	r;

	r = 1;
	while (p > 0)
	{
		r = r * n;
		p--;
	}
	return (r);
}

static int	get_length(int n)
{
	int	count;

	if (n == -2147483648)
		return (11);
	else if (n == 0)
		return (1);
	else if (n < 0)
	{
		n = -n;
		count = 1;
	}	
	else
		count = 0;
	while (n > 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

/* 
prints positive integer
 */
static void	positive_tostr(int n, int len)
{
	int	d;

	while (len != 0)
	{
		len--;
		d = power(10, len);
		ft_putchar_fd((char)(n / d + '0'), 1);
		n = n % d;
	}
}

int	int_putnbr(int n)
{
	int		len;
	int		number;
	int		ret;

	if (n == -2147483648)
		return (int_putstr("-2147483648"));
	len = get_length(n);
	ret = len;
	if (n >= 0)
		number = n;
	else
	{
		ft_putchar_fd('-', 1);
		number = -n;
		len--;
	}
	positive_tostr(number, len);
	return (ret);
}
