/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:20:18 by mrubina           #+#    #+#             */
/*   Updated: 2023/04/30 17:49:42 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
int		print_arg(void **pp, const char *pconv, va_list *lst);
void	get_arg(void **pp_to_arg, va_list *v_list, char flag);
int		convert(void *s, char flag, int b);
int		convert_to_hex(void *s, char flag);
int		convert_to_p(void *s, char flag);
int		add_pad(int n, char c);
int		int_putnbr(int n);
int		int_putchar(char c);
int		int_putstr(char *s);
int		hexx(int conv_flag);
int		s_c(int conv_flag);
int		x_x(int conv_flag);
int		d_i(int conv_flag);
int		xx_nz(int conv_flag, void *p_to_arg);
#endif
