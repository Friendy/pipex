/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   align_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:27:14 by mrubina           #+#    #+#             */
/*   Updated: 2023/04/26 15:18:23 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//return first digit if it's not zero
static const char	*first_nzd(const char *s)
{
	while (*s != '\0')
	{
		if (ft_isdigit(*s) && (*s != '0'))
			return (s);
		s++;
	}
	return (0);
}

//return first digit if zero
static const char	*first_zero(const char *s)
{
	while (*s != '\0')
	{
		if (ft_isdigit(*s))
		{
			if (*s == '0')
				return (s);
			else
				return (0);
		}
		else
			s++;
	}
	return (0);
}

/* 
get min width
(0)(min_width).(lim)
*/
int	get_min_width(const char *s)
{
	char		*lim_start;
	const char	*min_width_start;
	int			min_width;

	min_width = 0;
	lim_start = ft_strchr(s, '.');
	min_width_start = first_nzd(s);
	if (min_width_start != 0)
		min_width = ft_atoi(min_width_start);
	if ((lim_start) && (min_width_start > lim_start))
		min_width = 0;
	return (min_width);
}

//alignment type
char	get_al(const char *s)
{
	char	align_type;
	int		min_width_int;

	align_type = '5';
	min_width_int = get_min_width(s);
	if (ft_strchr(s, '-'))
		align_type = 'l';
	else if (first_zero(s))
		align_type = '0';
	else if (min_width_int > 0)
		align_type = ' ';
	return (align_type);
}
