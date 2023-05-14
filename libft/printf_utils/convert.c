/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:27:14 by mrubina           #+#    #+#             */
/*   Updated: 2023/04/26 19:34:46 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//prints unsigned
static int	to_unsigned(void *s)
{
	unsigned int	u;
	int				cnt;

	cnt = 0;
	u = *(unsigned int *)s;
	if (u > 2147483647)
	{
		cnt = cnt + int_putnbr(u / 10);
		cnt = cnt + int_putnbr((u - (u / 10) * 10));
	}
	else
		cnt = int_putnbr(u);
	return (cnt);
}

//printing hex prefix
int	hexx(int conv_flag)
{
	if ((conv_flag == 'x') || (conv_flag == 'p'))
		int_putstr("0x");
	if (conv_flag == 'X')
		int_putstr("0X");
	return (2);
}

int	convert(void *s, char flag, int b)
{
	int	cnt;

	cnt = 0;
	if (s == 0)
		return (0);
	if (flag == 'c')
		cnt = int_putchar(*((char *)s));
	else if ((flag == 's') && (s != 0))
		cnt = int_putstr(s);
	else if ((flag == 'p') && (b == 0))
		cnt = hexx('x') + convert_to_p(s, 'x');
	else if ((flag == 'p') && (b == 1))
		cnt = convert_to_p(s, 'x');
	else if ((flag == 'd') || (flag == 'i'))
	{
		if ((*((int *)s) == -2147483648) && (b != 0))
			cnt = int_putnbr(214748364) + int_putnbr(8);
		else
			cnt = int_putnbr(*((int *)s));
	}
	else if (flag == 'u')
		cnt = to_unsigned(s);
	else if ((flag == 'x') || (flag == 'X'))
		cnt = convert_to_hex(s, flag);
	return (cnt);
}
