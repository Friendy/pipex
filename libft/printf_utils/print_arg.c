/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:27:14 by mrubina           #+#    #+#             */
/*   Updated: 2023/03/08 14:15:58 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_arg(void **pp, const char *pconv, va_list *lst)
{
	int		cnt;
	
	cnt = 0;
	get_arg(pp, lst, *pconv);
	if ((*pconv == '%') || (*pp == 0))
		return (cnt);
	cnt = convert(*pp, *pconv, 0);
	free(*pp);
	*pp = NULL;
	return (cnt);
}
