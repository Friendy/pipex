/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:37:48 by mrubina           #+#    #+#             */
/*   Updated: 2023/05/18 23:17:57 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void error_handler(int type, char *name, int *exit_stat)
{
	int er_st;
	char *text;
	
	*exit_stat = 1;
	er_st = errno;
	if (type == 6)
		{ft_printf("Error: wrong number of arguments");
			er_st = 1;
		}
	if (type == ENOENT)
	{	
		text = ft_strjoin("pipex: ", name);
		perror(text);
		free(text);
		*exit_stat = 2;
	}
	if (type == 300)
	{	
		int_to_file(*exit_stat, "ex", 5, 'a');
		ft_putstr_fd(ft_strjoin("pipex: ", name), 2);
		ft_putendl_fd(": command not found", 2);
		*exit_stat = 127;
	}
		//ft_printf("%s", name);}
		//perror("No access to the file ");
	if (type == 1)
		perror("Could not create pipe");
	if (type == 200)
		perror("Could not create pipe");
	if (type == 3)
		perror("Could not duplicate process");
	if (type == 127)
		perror(strerror(127));
	if (type == 13)
		perror(name);
	if (type == 128)
		perror(strerror(128));
	if (type == 100)
	{
		perror(name);
		
	}
	
	if (*exit_stat != 127 && *exit_stat != 2)
		exit(*exit_stat);
}
