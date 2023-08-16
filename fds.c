/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:37:30 by mrubina           #+#    #+#             */
/*   Updated: 2023/08/14 21:31:44 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//open input file
int	inopen(int argc, char *name, int *status, int *pipestat)
{
	int	fd;

	*status = 0;
	*pipestat = 1;
	if (argc != 5)
		error_handler(ARG, "", status);
	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		error_handler(ENOENT, name, status);
		fd = open("/dev/null", O_RDONLY);
		*pipestat = 0;
	}
	return (fd);
}

//opens outfile
int	outopen(char *outfile, int *status)
{
	int	fd;

	if (access(outfile, W_OK) == -1 && errno == EACCES)
		error_handler(EACCES, outfile, status);
	else if (access(outfile, F_OK) == 0)
		unlink(outfile);
	fd = open(outfile, O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
		error_handler(ERR, "", status);
	return (fd);
}
