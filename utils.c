/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:37:30 by mrubina           #+#    #+#             */
/*   Updated: 2023/08/10 18:49:35 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*replace_char(char *str, char *str_end, char old_c, char new_c)
{
	char	*map;
	int		i;

	i = 0;
	map = malloc(str_end - str + 2);
	if (map == NULL)
		return (map);
	while (str != str_end)
	{
		if (*str == old_c)
		{
			*str = new_c;
			map[i] = 'c';
		}
		else
			map[i] = 'm';
		str++;
		i++;
	}
	map[i + 1] = '\0';
	return (map);
}

void	replace_by_map(char *str, char *map, char c)
{
	while (map != NULL && *map != '\0')
	{
		if (*map == 'c')
			*str = c;
		map++;
		str++;
	}
}

void	free_arr(char **arr)
{
	char	**i;

	if (arr != NULL)
	{
		i = arr;
		while (*i != NULL)
		{
			free(*i);
			i++;
		}
		free(arr);
	}
}

void	free_str(char *s)
{
	if (s != NULL)
	{
		free(s);
		s = NULL;
	}
}

//redirecting file descriptor to stdin/stddout and closing it
void	redir_close(int fd, int stdfd, int *status)
{
	if (dup2(fd, stdfd) == -1)
		error_handler(ERR, "", status);
	if (close(fd) == -1)
		error_handler(ERR, "", status);
}
