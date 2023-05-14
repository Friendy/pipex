/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:27:14 by mrubina           #+#    #+#             */
/*   Updated: 2023/05/02 01:43:23 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_p_size(char flag)
{
	if (flag == 'c')
		return (sizeof(int));
	else if (flag == 'p')
		return (sizeof(void *));
	else if ((flag == 'd') || (flag == 'i'))
		return (sizeof(int));
	else if (flag == 'u')
		return (sizeof(unsigned int));
	else if ((flag == 'x') || (flag == 'X'))
		return (sizeof(unsigned int));
	else
		return (0);
}

static char	*get_string(va_list *v_list)
{
	char	*s;	
	char	*p_to_str;
	
	s = va_arg(*v_list, char *);

	if (s == NULL)
		s = "(null)";
	p_to_str = malloc((ft_strlen(s) + 1));
	ft_strlcpy(p_to_str, s, ft_strlen(s) + 1);
	return (p_to_str);
}

void	get_arg(void **pp_to_arg, va_list *v_list, char flag)
{
	void	*p_to_arg;
	int		size;

	p_to_arg = 0;
	size = get_p_size(flag);
	if ((size != 0) && (flag != 's') && ((flag == 'c') || !s_c(flag)))
		p_to_arg = malloc(size);
	if (flag == 's')
		p_to_arg = get_string(v_list);
	else if (flag == 'c')
		*((char *)p_to_arg) = va_arg(*v_list, int);
	else if (flag == 'p')
		*((void **)p_to_arg) = va_arg(*v_list, void *);
	else if ((flag == 'd') || (flag == 'i'))
		*((int *)p_to_arg) = va_arg(*v_list, int);
	else if (flag == 'u')
		*((unsigned int *)p_to_arg) = va_arg(*v_list, unsigned int);
	else if ((flag == 'x') || (flag == 'X'))
		*((unsigned int *)p_to_arg) = va_arg(*v_list, unsigned int);
	*pp_to_arg = p_to_arg;
}
