/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:37:48 by mrubina           #+#    #+#             */
/*   Updated: 2023/05/20 16:41:32 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// 6, 127, 300, 400

void static	print_error(char *name, char *text, int use_perr)
{
	char	*t;

	if (use_perr == 0)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(name, 2);
		if (text != NULL)
			ft_putendl_fd(text, 2);
		else
			ft_putchar_fd('\n', 2);
	}
	else
	{
		if (text == NULL)
			perror(name);
		else
		{
			t = ft_strjoin(text, name);
			perror(t);
			free(t);
		}
	}	
}

void	error_handler(int type, char *name, int *exit_stat)
{
	*exit_stat = 1;
	if (type == 6)
		print_error("wrong number of arguments", 0, 0);
	else if (type == ENOENT)
		print_error(name, "pipex: ", 1);
	else if (type == 300 || type == 400)
	{
		print_error(name, ": command not found", 0);
		*exit_stat = 127;
	}
	else if (type == 127)
		perror("pipex");
	else if (type == 13)
		perror(name);
	else if (type == 14 || type == 15)
	{	
		if (type == 15)
			print_error("", strerror(13), 0);
		else
			print_error(name, "pipex: ", 1);
		*exit_stat = 126;
	}
	if (type != 300 && type != ENOENT)
		exit(*exit_stat);
}
