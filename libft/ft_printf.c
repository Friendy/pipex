/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:27:14 by mrubina           #+#    #+#             */
/*   Updated: 2023/05/02 00:37:30 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_utils/ft_printf.h"

/* 
format structure
"text %conversion text ..."
conversion structure
%(conversion symbol)
 */

static int	print_txt(const char *txt, const char *srch, const char **next)
{
	const char	*str;
	int			cnt;

	str = "";
	cnt = 0;
	if (srch == 0)
		return (0);
	*next = ft_strchr(srch, '%');
	if (*next != 0)
		str = ft_substr(txt, 0, *next - txt);
	if ((str) && (*next != 0))
	{
		cnt = cnt + int_putstr((char *)str);
		free((void *)str);
	}
	if (*next == 0)
	{
		str = txt;
		cnt = cnt + int_putstr((char *)str);
	}
	return (cnt);
}

static int	print_percent(const char **next_format, const char *conv_end)
{
	*next_format = conv_end + 1;
	return (int_putchar('%'));
}

int	ft_printf(const char *format, ...)
{
	va_list		v_list;
	void		**pp_to_arg;
	const char	*next_format;
	const char	*conv_end;
	int			cnt;
	
	next_format = format;
	pp_to_arg = malloc(sizeof(void **));
	va_start(v_list, format);
	cnt = print_txt(format, format, &next_format);
	while (next_format)
	{
		next_format++;
		conv_end = next_format;
		if ((conv_end != 0) && (*conv_end == '%'))
			cnt = cnt + print_percent(&next_format, conv_end);
		else if ((pp_to_arg != 0) && (conv_end != 0))
			cnt = cnt + print_arg(pp_to_arg, conv_end, &v_list);
		cnt = cnt + print_txt(conv_end + 1, next_format, &next_format);
	}
	va_end(v_list);
	free(pp_to_arg);
	return (cnt);
}
