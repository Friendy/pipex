/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:37:48 by mrubina           #+#    #+#             */
/*   Updated: 2023/05/20 21:29:00 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* ./pipex file1 cmd cmd2 file2 
*/

//open file, set stdin, create pipe
static int	create_pipe(int argc, char *name, int *pipefd, int *status)
{
	int	fd;

	*status = 0;
	if (argc != 5)
		error_handler(6, "", status);
	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		error_handler(ENOENT, name, status);
		fd = open("/dev/null", O_RDONLY);
		if (fd < 0)
			error_handler(ENOENT, name, status);
	}
	if (dup2(fd, 0) == -1 || pipe(pipefd) == -1)
		error_handler(100, "", status);
	return (fd);
}

// parent process: close input file, close write end, open output file, 
//redirect stdin to write end, redirect stdout to file,
static void	redirect(int *p, int f, char *outfile, int *status)
{
	if (close(f) == -1 || close(p[1]) == -1)
		error_handler(100, "", status);
	if (access(outfile, W_OK) == -1 && errno == EACCES)
		error_handler(13, outfile, status);
	else if (access(outfile, F_OK) == 0)
		unlink(outfile);
	f = open(outfile, O_CREAT | O_WRONLY, 0644);
	if (f < 0 || dup2(p[0], 0) == -1 || dup2(f, 1) == -1 || close(p[0]) == -1)
		error_handler(100, "", status);
}

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
			error_handler(100, "", &status);
	}
	if (execve(cmd_path, cmd_args, envp) == -1)
		error_handler(300, cmd_path, &status);
	return (status);
}

static int	wait_end(int id, int *status, int fd)
{
	if (waitpid(id, status, 0) == -1 || close(fd) == -1)
		error_handler(100, "", status);
	return (WEXITSTATUS(*status));
}

int	main(int argc, char *argv[], char *envp[])
{
	pid_t	id;
	int		pipefd[2];
	int		filefd;
	int		status;

	filefd = create_pipe(argc, argv[1], pipefd, &status);
	id = fork();
	if (id == -1)
		error_handler(100, "", &status);
	else if (id == 0)
		return (child_process(argv[2], envp, pipefd));
	else
	{
		redirect(pipefd, filefd, argv[4], &status);
		id = fork();
		if (id == -1)
			error_handler(100, "", &status);
		else if (id == 0)
			return (child_process(argv[3], envp, 0));
		else
			return (wait_end(id, &status, filefd));
	}
}
