/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:37:30 by mrubina           #+#    #+#             */
/*   Updated: 2023/08/16 19:51:40 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

//open input file
int	inopen(char *name, int *status, int *pipestat)
{
	int	fd;

	if (pipestat[0] == HERE_DOC)
		return (0);
	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		error_handler(ENOENT, name, status);
		fd = open("/dev/null", O_RDONLY);
		pipestat[1]--;
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
