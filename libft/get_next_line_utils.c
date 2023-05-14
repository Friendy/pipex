/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:27:14 by mrubina           #+#    #+#             */
/*   Updated: 2023/04/26 15:12:15 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* allocates buffer if needed
and initiates some variables
*/
char	*init_params(int fd, char *buf, int *curr, ssize_t *rd)
{
	if (!buf)
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf != NULL)
		{
			*rd = read(fd, buf, BUFFER_SIZE);
			if (rd > 0)
				*curr = *rd - 1;
		}
	}
	else
	{
		*curr = 0;
		while (buf[*curr] != '\0')
			(*curr)++;
		(*curr)--;
		*rd = BUFFER_SIZE;
	}
	return (buf);
}

/* 
returns the number of copied characters til new line
or zero if the new_line is not reached
 */
int	cpy_til_nl(int last_rd, char *buf, char *temp)
{
	int	ind;

	if (buf == NULL || temp == NULL )
		return (0);
	ind = 0;
	while ((ind <= last_rd && buf[ind] != '\n'))
	{
		temp[ind] = buf[ind];
		ind++;
	}
	if (ind <= last_rd && buf[ind] == '\n')
	{
		temp[ind] = '\n';
		temp[ind + 1] = '\0';
		return (ind + 1);
	}
	else
	{
		temp[last_rd + 1] = '\0';
		return (0);
	}	
}

/* 
returns the part of the text that we should store for next calls
[part to be returned during this call] [part to be returned during next calls]
[part to be returned during this call]
 */
char	*buf_diff(char *small, char *big, int last_ind)
{
	int		ind;
	int		shift;
	char	*buf;

	ind = 0;
	while (big && small && (ind <= last_ind) && (big[ind] == small[ind]))
		ind++;
	shift = ind;
	buf = malloc(last_ind - shift + 2);
	if (buf == NULL || small == NULL || big == NULL )
		return (big);
	while (ind <= last_ind)
	{
		buf[ind - shift] = big[ind];
		ind++;
	}
	buf[ind - shift] = '\0';
	free(big);
	if (ind - shift == 0)
	{
		free(buf);
		buf = 0;
	}
	return (buf);
}

char	*resize(char *buf, int last_ind)
{
	char	*temp;
	int		i;

	if (buf == NULL)
		return (buf);
	i = 0;
	temp = malloc(last_ind + 2);
	if (temp == NULL)
		return (temp);
	temp[last_ind + 1] = '\0';
	while (i <= last_ind - BUFFER_SIZE)
	{
		temp[i] = buf[i];
		i++;
	}
	free (buf);
	return (temp);
}

char	*free_bufs(char **buf1, char **buf2)
{
	if (*buf2 == NULL)
	{
		if (*buf1)
			free(*buf1);
		return (*buf2);
	}
	if (*buf1 == NULL)
	{
		if (*buf2)
			free(*buf2);
		return (*buf1);
	}
	else
	{
		free(*buf1);
		free(*buf2);
		*buf1 = NULL;
		return (*buf1);
	}
}
