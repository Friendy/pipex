/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:37:30 by mrubina           #+#    #+#             */
/*   Updated: 2023/05/18 18:24:25 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char *replace_char(char *str, char *str_end, char old_c, char new_c)
{
	char *map;
	int i;
	
	i = 0;
	map = malloc(str_end - str + 2);
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

void replace_by_map(char *str, char *map, char c)
{
	while (*map != '\0')
	{
		if (*map == 'c')
			*str = c;
		map++;
		str++;
	}
}

void free_arr(char **arr)
{
	char **i;

	i = arr;
	while (*i != NULL)
	{
		free(*i);
		i++;	
	}
	free(arr);
}



void pipe_info(int *pipefd)
{
	printf("read end:%i (%p)\n", pipefd[0], pipefd);
	printf("write end:%i (%p)\n", pipefd[1], (pipefd + 1));
}

void arr_info(char **arr)
{
	int	i;
	
	i = 0;
	while (arr[i] != NULL)
	{
		printf("%i: %s(%p)[%p]\n", i, arr[i], arr[i], &arr[i]);
		i++;
	}
}

void info_to_file(char **arr, char  *file)
{
	int	i;
	int fd;
	static int count = 0;
	
	i = 0;
	fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	ft_putnbr_fd(count, fd);
	while (arr[i] != NULL)
	{
		ft_putnbr_fd(i, fd);
		ft_putchar_fd(' ', fd);
		ft_putendl_fd(arr[i], fd);
		i++;
	}
	close(fd);
	count = count + 1;
}

void get_var(char *var_name, char *file, int flag)
{
	int fd;
	if (flag == 'a')
		fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		fd = open(file, O_CREAT | O_WRONLY, 0644);
	ft_putendl_fd(getenv(var_name), fd);
	close(fd);
}

void int_to_file(int i, char *file, int id, int flag)
{
	int fd;
	
	if (flag == 'a')
		fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		fd = open(file, O_CREAT | O_WRONLY, 0644);
	ft_putnbr_fd(id, fd);
	ft_putstr_fd(": ", fd);
	ft_putnbr_fd(i, fd);
	ft_putchar_fd('\n', fd);
	close(fd);
}

void str_to_file(char *str, char *file, int id, int flag)
{
	int fd;
	
	if (flag == 'a')
		fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		fd = open(file, O_CREAT | O_WRONLY, 0644);
	ft_putnbr_fd(id, fd);
	ft_putstr_fd(": ", fd);
	ft_putendl_fd(str, fd);
	close(fd);
}

