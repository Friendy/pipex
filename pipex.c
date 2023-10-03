/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:37:48 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/03 14:23:52 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* ./pipex file1 cmd cmd2 file2
*/

// creates pipe
static void	create_pipe(int *pipefd, int *status)
{
	if (pipe(pipefd) == -1)
		error_handler(ERR, "", status);
}

//closes pipe input (because it's parent)
//sets pipe output to stdin
/* static void	redirect(int *p, int *status, int pipestat)
{
	if (pipestat == 1)
	{
		if (close(p[1]) == -1)
			error_handler(ERR, "", status);
		redir_close(p[0], 0, status);
	}
} */

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

static int	create_child(char *cmd, char *envp[], int *pipefd, pid_t *id)
{
	char	**cmd_args;
	char	*cmd_path;
	int		status;

	status = 0;
	//dprintf(2, "my id%i\n", id[0]);
	*id = fork();
	if (*id == -1) //test return here
		error_handler(ERR, "", &status);
	if (*id == 0)
	{
		cmd_args = get_args(cmd);
		cmd_path = find_path(*cmd_args, envp, &status);
		if (pipefd != NULL)
		{
			if (close(pipefd[0]) == -1 || dup2(pipefd[1], 1) == -1)
				error_handler(ERR, "", &status);
		}
		//dprintf(2, "before exec%i\n", *id);
		if (execve(cmd_path, cmd_args, envp) == -1)
			error_handler(NFOUND, cmd_path, &status);
	}
	return (status);
}

//wait till the last child returns and close outfile
/* static int	wait_end(int id, int *status, int fd)
{
	if (waitpid(id, status, 0) == -1 || close(fd) == -1)
		error_handler(ERR, "", status);
	return (WEXITSTATUS(*status));
} */

static int	wait_end(int *id, int *status, int fd, int pipestat)
{
	if (pipestat == 1)
	{
		if (waitpid(id[0], status, WNOHANG) == -1)
			error_handler(ERR, "", status);
	}
	if (waitpid(id[1], status, 0) == -1 || close(fd) == -1)
		error_handler(ERR, "", status);
	return (WEXITSTATUS(*status));
}

int	main(int argc, char *argv[], char *envp[])
{
	pid_t	id[2];
	int		pipefd[2];
	int		filefd;
	int		status;
	int		pipestat;

	filefd = inopen(argc, argv[1], &status, &pipestat);
	if (pipestat == 1)
		create_pipe(pipefd, &status);
	redir_close(filefd, 0, &status);
	if (pipestat == 1)
	{
		create_child(argv[2], envp, pipefd, &id[0]);
		if (close(pipefd[1]) == -1)
			error_handler(ERR, "", &status);
		redir_close(pipefd[0], 0, &status);
	}
	filefd = outopen(argv[4], &status);
	if (dup2(filefd, 1) == -1)
		error_handler(ERR, "", &status);
 	create_child(argv[3], envp, NULL, &id[1]);
	return (wait_end(id, &status, filefd, pipestat));
}
