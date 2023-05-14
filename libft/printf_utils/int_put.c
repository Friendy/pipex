/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:36:12 by mrubina           #+#    #+#             */
/*   Updated: 2023/04/26 19:36:32 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	int_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	int_putstr(char *s)
{
	int	cnt;

	cnt = 0;
	while ((s != 0) && (*s != '\0'))
	{
		cnt = cnt + int_putchar(*s);
		s++;
	}
	return (cnt);
}
