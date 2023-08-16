/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:37:48 by mrubina           #+#    #+#             */
/*   Updated: 2023/08/15 22:47:53 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* ./pipex file1 cmd cmd2 file2
*/

// creates pipe and redirects file descriptor of some file
static void	create_pipe(int *pipefd, int *status)
{
	if (pipe(pipefd) == -1)
		error_handler(ERR, "", status);
}

//opens outfile and redirects it to stdout
//closes pipe input (because it's parent)
//sets pipe output to stdin
static void	redirect(int *p, char *outfile, int *status, int np)
{
	int	filefd;

	filefd = outopen(outfile, status);
	if (dup2(filefd, 1) == -1)
		error_handler(ERR, "", status);
	if (np == 1)
	{
		if (close(p[1]) == -1)
			error_handler(ERR, "", status);
		redir_close(p[0], 0, status);
	}
}

/* void check_args(int argc, char *arg1, int *pipestat, int *status)
{
	*status = 0;
	if (argc == 6 && strcmp(arg1, "here_doc") == 0)
		*pipestat = 2;
	else if (argc != 5)
		*pipestat = 1;
	else
		error_handler(ARG, "", status);
} */

static int	child_process(char *cmd, char *envp[], int *pipefd)
{
	char	**cmd_args;
	char	*cmd_path;
	int		status;

	status = 0;
	cmd_args = get_args(cmd);
	cmd_path = find_path(*cmd_args, envp, &status);
	if (pipefd != 0)
	{
		if (close(pipefd[0]) == -1 || dup2(pipefd[1], 1) == -1)
			error_handler(ERR, "", &status);
	}
	if (execve(cmd_path, cmd_args, envp) == -1)
		error_handler(NFOUND, cmd_path, &status);
	return (status);
}

//wait till the last child returns and close outfile
static int	wait_end(int id, int *status, int fd)
{
	if (waitpid(id, status, 0) == -1 || close(fd) == -1)
		error_handler(ERR, "", status);
	return (WEXITSTATUS(*status));
}

int	main(int argc, char *argv[], char *envp[])
{
	pid_t	id;
	int		pipefd[2];
	int		filefd;
	int		status;
	int		pipestat;

	filefd = inopen(argc, argv[1], &status, &pipestat);
	if (pipestat == 1)
		create_pipe(pipefd, &status);
	redir_close(filefd, 0, &status);
	if (pipestat == 1)
		id = fork();
	if (pipestat == 1 && id == -1) //test return here
		error_handler(ERR, "", &status);
	else if (pipestat == 1 && id == 0)
		return (child_process(argv[2], envp, pipefd));
	else
	{
		redirect(pipefd, argv[4], &status, pipestat);
		id = fork();
		if (id == -1)
			error_handler(ERR, "", &status);
		else if (id == 0)
			return (child_process(argv[3], envp, 0));
		else
			return (wait_end(id, &status, filefd));
	}
}

/* int	main(int argc, char *argv[], char *envp[])
{
	pid_t	id;
	int		pipefd[2];
	int		filefd;
	int		status;
	int		pipestat;

	filefd = inopen(argc, argv[1], &status, &pipestat);
	redir_close(filefd, 0, &status);
	redirect(pipefd, argv[4], &status, pipestat);
	id = fork();
	if (id == -1)
		error_handler(ERR, "", &status);
	else if (id == 0)
		return (child_process(argv[3], envp, 0));
	else
		return (wait_end(id, &status, filefd));
} */
