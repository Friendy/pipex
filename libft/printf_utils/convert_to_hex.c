/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:27:14 by mrubina           #+#    #+#             */
/*   Updated: 2023/04/26 19:34:41 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// convert decimal digit into hex digit to be used as char
static	int	hex_digit(int n, int flag)
{
	int	c;

	c = 0;
	if ((n >= 0) && (n < 10))
		c = '0' + n;
	else if ((n > 9) && (n < 16) && (flag == 'x'))
		c = 'a' + n - 10;
	else if ((n > 9) && (n < 16) && (flag == 'X'))
		c = 'A' + n - 10;
	return (c);
}

static int	put_reverse(char *buf, int i)
{
	int	cnt;

	cnt = 0;
	while (i >= 0)
	{
		cnt = cnt + int_putchar(buf[i]);
		i--;
	}
	return (cnt);
}

//large decimal numbers to hex numbers, 8 bytes
static int	tohex(unsigned long n, int flag)
{
	int		remainder;
	char	*buf;
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	buf = malloc(16);
	if (n == 0)
	{
		buf[i] = '0';
		i++;
	}
	while (n > 0)
	{
		remainder = n % 16;
		n = n / 16;
		buf[i] = hex_digit(remainder, flag);
		i++;
	}
	i--;
	cnt = put_reverse(buf, i);
	free(buf);
	return (cnt);
}

//to hexadecimal, 4 bytes
int	convert_to_hex(void *p_to_n, char flag)
{
	unsigned int	n;

	n = *(unsigned int *)p_to_n;
	return (tohex(n, flag));
}

int	convert_to_p(void *p_to_n, char flag)
{
	unsigned long	n;

	n = *(unsigned long *)p_to_n;
	return (tohex(n, flag));
}
