/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:27:14 by mrubina           #+#    #+#             */
/*   Updated: 2023/04/26 15:12:23 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_next_line(int fd, char **p_buf)
{
	char		*temp;
	int			new_ln;
	int			curr;
	ssize_t		rd;

	if (!p_buf)
		return (0);
	temp = malloc(BUFFER_SIZE + 1);
	*p_buf = init_params(fd, *p_buf, &curr, &rd);
	if (*p_buf == NULL || temp == NULL || rd <= 0)
		return (free_bufs(p_buf, &temp));
	new_ln = cpy_til_nl(curr, *p_buf, temp);
	while (!new_ln && rd == BUFFER_SIZE)
	{
		*p_buf = resize(*p_buf, curr + BUFFER_SIZE);
		temp = resize(temp, curr + BUFFER_SIZE);
		if (*p_buf)
			rd = read(fd, &((*p_buf)[curr + 1]), BUFFER_SIZE);
		if (*p_buf == NULL || temp == NULL || rd < 0)
			return (free_bufs(p_buf, &temp));
		new_ln = cpy_til_nl(rd - 1, &((*p_buf)[curr + 1]), &temp[curr + 1]);
		curr = curr + rd;
	}
	*p_buf = buf_diff(temp, *p_buf, curr);
	return (temp);
}

char	**free_arr(char **arr, int last_ind)
{
	int	i;

	i = 0;
	while (arr && i <= last_ind && arr[i] == NULL)
		i++;
	if (arr && i > last_ind)
	{
		free(arr);
		arr = NULL;
	}
	return (arr);
}

char	*get_next_line(int fd)
{
	static char	**bufs;
	char		*temp;
	int			i;
	int			arr_size;

	i = 0;
	arr_size = 10240;
	if (!bufs)
	{
		bufs = malloc(arr_size * sizeof(char *));
		while (i <= arr_size - 1)
		{
			bufs[i] = NULL;
			i++;
		}
	}
	if (fd < 0 || fd > arr_size - 1)
		temp = NULL;
	else
		temp = read_next_line(fd, (bufs + fd));
	bufs = free_arr(bufs, arr_size - 1);
	return (temp);
}
