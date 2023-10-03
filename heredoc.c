/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/03 21:07:15 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

//writes buffer to file
void	wrtofile(int end, int filefd, char *cur, char *buf)
{
	if (*cur == '\n')
	{
		if (!end)
		{
			write(filefd, buf, cur - buf + 1);
			write(1, "> ", 3);
		}
	}
	else
		{
			write(filefd, buf, cur - buf);}
}

//reads from stdin untill either the buffer is full or till newline
//returns the pointer to the last filled character of the buffer
char	*readbuf(char *buf, int size)
{
	char	*cur;

	cur = buf;
	ft_bzero(buf, size + 1);
	while (cur <= (buf + size - 1) && *cur != '\n')
	{
		read(0, cur, 1);
		if (*cur != '\n')
			cur = cur + 1;
	}
	return (cur);
}


/* checking delimiter after each newine
buffer variants
|text\n     | |delimiter\n| - don't write into the file  !!!
|texttexttex| |delimiter\n| - write the whole buffer to the file !!!
|texttexttex| - write the whole buffer to the file
|text\n     | - write the part of the buffer including \n
*/
static int	nlupdate(char *cur, int isdlm, int prevnl, int flag)
{
	if (flag == 1 && *cur == '\n' && isdlm == TRUE)
		return (TRUE);
	else if (flag == 0)
	{
		if (*cur != '\n')
			return (FALSE);
		if (*cur == '\n' && isdlm == FALSE)
			return (TRUE);
	}
	return (prevnl);
}

/*
reads from stdin untill delimiter and writes into a file
prevnl is TRUE if previous buffer ended with newline
 */
static int	stdintofd(char *dlm, int filefd)
{
	char	*buf;
	char	*cur;
	int		size;
	int		prevnl;
	int		isdlm;

	prevnl = TRUE;
	isdlm = FALSE;
	size = ft_strlen(dlm) + 1;
	buf = malloc((size + 1) * sizeof(char));
	if (buf == NULL)
		return (1);
	cur = buf;
	write(1, "> ", 3);
	while (isdlm == FALSE || *(buf + size - 1) != '\n' || prevnl == 0)
	{
		prevnl = nlupdate(cur, isdlm, prevnl, 1);
		cur = readbuf(buf, size);
		//dprintf(2, "buf %s\n", buf);
		//exit(0);
		isdlm = (ft_strncmp(buf, dlm, size - 1) == 0);
		wrtofile((isdlm == TRUE && prevnl == TRUE), filefd, cur, buf);
		prevnl = nlupdate(cur, isdlm, prevnl, 0);
	}
	//exit(0);
	free(buf);
	buf = NULL;
	return (0);
}

void	heredoc(char *dlm, int *status)
{
	int	fd;

	if (access("tmp", F_OK) == 0)
		unlink("tmp");
	fd = open("tmp", O_CREAT | O_RDWR, 0644);
	if (fd >= 0)
	{
		if (stdintofd(dlm, fd) == 1)
			error_handler(ENOENT, "tmp", status);//!!!!
		close(fd);
	}
}
