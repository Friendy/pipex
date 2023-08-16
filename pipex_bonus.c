/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:37:48 by mrubina           #+#    #+#             */
/*   Updated: 2023/08/16 22:58:53 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
static void	redirect(int *p, int filefd, int *status, int pipestat)
{
	//printf("ddfd%i\n", filefd);
	if (dup2(filefd, 1) == -1)
		error_handler(ERR, "", status);
	//printf("ddfd%i\n", pipestat);
	if (pipestat == 1)
	{
		//exit(0);
		if (close(p[1]) == -1)
			error_handler(ERR, "", status);
		redir_close(p[0], 0, status);
	}
}

static void	redirect1(int *p, int *pipefd, int *status, int pipestat)
{
//output to next pipe
	//exit(0);
	if (dup2(pipefd[1], 1) == -1)
		error_handler(ERR, "", status);
	//exit(0);
	//printf("ddfd%i\n", pipefd[1]);
	if (pipestat != 0)
	{
		if (close(p[1]) == -1)
			error_handler(ERR, "", status);
		redir_close(p[0], 0, status);
	}
}

static int	child_process(char *cmd, char *envp[], int *pipefd)
{
	char	**cmd_args;
	char	*cmd_path;
	int		status;

	status = 0;
	cmd_args = get_args(cmd);
	cmd_path = find_path(*cmd_args, envp, &status);
	//printf("child%s\n", cmd);

	if (pipefd != NULL)
	{
		if (close(pipefd[0]) == -1 || dup2(pipefd[1], 1) == -1)
			error_handler(ERR, "", &status);
	}
	if (execve(cmd_path, cmd_args, envp) == -1)
		error_handler(NFOUND, cmd_path, &status);
	return (status);
}

//wait till the last child returns and close outfile
static int	wait_end(int *id, int *pipestat, int *status, int fd)
{
	int	i;

	i = 0;
	if (pipestat[0] == HERE_DOC)
		i = 1;
	while (i <= pipestat[1] - 1)
	{
		if (waitpid(id[i], status, 0) == -1)
			error_handler(ERR, "", status);
		i++;
	}
	return (WEXITSTATUS(*status));
}

void check_args(int argc, char *arg1, int *pipestat, int *status)
{
	int len;

	if (argc < 5)
		error_handler(ARG, "", status);
	*status = 0;
	len = ft_strlen(arg1);
	if (argc == 6 && len == 8 && ft_strncmp(arg1, "here_doc", len) == 0)
		pipestat[0] = HERE_DOC;
	else
		pipestat[0] = NORM;
	pipestat[1] = argc - 3;
}

// 0 shoul go into pipe
void	here_doc(int *pipestat, int *pipefd, char *lm, int ind, int *status)
{
	if (pipestat[0] == HERE_DOC && ind == 0)
	{
		//printf("hd%i\n", pipefd[0]);
		//redir_close(pipefd[1], 0, status);
		if (dup2(0, pipefd[1]) == -1)
			error_handler(ERR, "", status);
		if (close(pipefd[0]) == -1)
			error_handler(ERR, "", status);
		write(1, ">", 2);
		if (close(pipefd[1]) == -1)
			error_handler(ERR, "", status);
		exit(0);
	}
	//*flag = 10;

}

//in case of child process main should return
int onefork(char *cmd, char *envp[], int *status, int *pipefd)
{
	pid_t	id;
	//int		pipefd[2];
	//int		pipestat;

	id = fork();
	//printf("%i\n", id);
	if (id == -1)
		error_handler(ERR, "", status);
	else if (id == 0)
		return (child_process(cmd, envp, pipefd)); //returns child process status , -1 if unsuccesssful
	return (id);
}

//[] [] []
//[] [] []
//
/*
pipestat = argc - 3 - number of processes
argc - 4 - number of pipes
pipestat -

with here_doc write into pipe directly [1] (copy [1], 0)

 */
int	main(int argc, char *argv[], char *envp[])
{
	pid_t	id[argc - 3];
	int		fds[(argc - 4)*2 + 2];
	int		status;
	int		pipestat[2];
	int		i;

	i = 0;
	check_args(argc, argv[1], pipestat, &status);
	fds[(argc - 4)*2] = inopen(argv[1], &status, pipestat);
	redir_close(fds[(argc - 4)*2], 0, &status);
	while (i <= pipestat[1] - 2)
	{
		create_pipe(&fds[2 * i], &status);
		id[i] = onefork(argv[i + 2], envp, &status, &fds[2*i]);
		if (id[i] == -1)
			return (1);
		//here_doc(pipestat, &fds[2 * i], argv[2], i, &status);
		if (close(fds[2*i + 1]) == -1)
			error_handler(ERR, "", &status);
		redir_close(fds[2*i], 0, &status);
		i++;
	}
	fds[(argc - 4)*2 + 1] = outopen(argv[argc - 1], &status);
	redir_close(fds[(argc - 4)*2 + 1], 1, &status);
	id[i] = onefork(argv[argc - 2], envp, &status, NULL);
	if (id[i] == -1)
		return (1);
	return (wait_end(id, pipestat, &status, fds[(argc - 4)*2 + 1]));
}
