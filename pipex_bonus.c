/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:37:48 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/04 12:58:06 by mrubina          ###   ########.fr       */
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

/* static int	create_child(char *cmd, char *envp[], int *pipefd)
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
} */

//wait till the last child returns and close outfile
static int	wait_end(int *id, int *flags, int *status, int argc)
{
	int	i;
	int flag;

	i = 0;
	flag = WNOHANG;
	i = flags[1];
	while (i <= argc - 4)
	{
		if (i == argc - 4)
			flag = 0;
		if (waitpid(id[i], status, flag) == -1)
			error_handler(ERR, "", status);
		i++;
	}
	return (WEXITSTATUS(*status));
}

static int	wait_end1(int *id, int *status, int fd, int pipestat)
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

void check_args(int argc, char *arg1, int *flags, int *status)
{
	int len;

	if (argc < 5)
		error_handler(ARG, "", status);
	*status = 0;
	len = ft_strlen(arg1);
	if (argc == 6 && len == 8 && ft_strncmp(arg1, "here_doc", len) == 0)
		flags[0] = HERE_DOC;
	else
		flags[0] = NORM;
	flags[1] = 0;
	//dprintf(2, "hd%i\n", pipestat[0]);
}

// 0 shoul go into pipe

static int	create_child(char *cmd, char *envp[], int *pipefd, pid_t *id)
{
	char	**cmd_args;
	char	*cmd_path;
	int		status;

	status = 0;
	*id = fork();
	if (*id == -1) //test return here
		error_handler(ERR, "", &status);
	if (*id == 0)
	{
		cmd_args = get_args(cmd);
		cmd_path = find_path(cmd_args, envp, &status);
		if (pipefd != NULL)
		{
			if (close(pipefd[0]) == -1 || dup2(pipefd[1], 1) == -1)
				error_handler(ERR, "", &status);
		}
		if (execve(cmd_path, cmd_args, envp) == -1)
			error_handler(NFOUND, cmd_path, &status);
	}
	return (status);
}



//[] [] []
//[] [] []
//
/*
pipestat[1] = argc - 3 - number of processes
argc - 4 - number of pipes
pipestat[0] - here_doc

with here_doc write into pipe directly [1] (copy [1], 0)

 */
/* int	main(int argc, char *argv[], char *envp[])
{
	pid_t	*id;
	int		*fds;
	int		status;
	int		pipestat[2];
	int		i;

	i = 0;
	check_args(argc, argv[1], pipestat, &status);
	id = malloc(sizeof(int) * argc - 3);
	fds = malloc(sizeof(int) * ((argc - 4)*2 + 2));
	//fds = malloc(sizeof(int) * 4);
	fds[(argc - 4)*2] = inopen(argv[1], &status, pipestat);
	//fds[2] = inopen(argv[1], &status, pipestat);
	redir_close(fds[(argc - 4)*2], 0, &status);
	//if (pipestat[1] == argc - 4)
		i = pipestat[1];
	//redir_close(fds[2], 0, &status);
	while (i <= argc - 5)
	{
		//create_pipe(&fds[0], &status);
		create_pipe(&fds[2 * i], &status);
		create_child(argv[i + 2], envp, &fds[2*i], &id[i]);
		//create_child(argv[i + 2], envp, &fds[0], &id[i]);
		//here_doc(pipestat, &fds[2 * i], argv[2], i, &status);
		//if (close(fds[1]) == -1)
		if (close(fds[2 * i + 1]) == -1)
			error_handler(ERR, "", &status);
		redir_close(fds[2 * i], 0, &status);
		//redir_close(fds[0], 0, &status);
		i++;
	}
	fds[(argc - 4)*2 + 1] = outopen(argv[argc - 1], &status);
	//fds[3] = outopen(argv[argc - 1], &status);
	redir_close(fds[(argc - 4)*2 + 1], 1, &status);
	//redir_close(fds[3], 1, &status);
	create_child(argv[i + 2], envp, NULL, &id[argc - 4]);
	return (wait_end(id, pipestat, &status, argc));
	//return (wait_end(id, pipestat, &status, fds[3]));
} */

/* int	heredocm(int argc, char *argv[], char *envp[])
{
	pid_t	id[2];
	int		pipefd[2];
	int		filefd;
	int		status;
	int		pipestat;

	heredoc(argv[2], &status);
	filefd = inopen("tmp", &status, &pipestat);
	if (pipestat == 1)
		create_pipe(pipefd, &status);
	redir_close(filefd, 0, &status);
	if (pipestat == 1)
	{
		create_child(argv[3], envp, pipefd, &id[0]);
		if (close(pipefd[1]) == -1)
			error_handler(ERR, "", &status);
		redir_close(pipefd[0], 0, &status);
	}
	filefd = outopen(argv[5], &status);
	if (dup2(filefd, 1) == -1)
		error_handler(ERR, "", &status);
 	create_child(argv[4], envp, NULL, &id[1]);
	return (wait_end1(id, &status, filefd, pipestat));
} */


/* 
flag0 here_doc or norm
flag1 file err
flag2 1 argc or 5
 */
void init(pid_t **id, int **fds, int *flags, int argc)
{
	if (flags[0] == HERE_DOC)
	{
		*id = malloc(sizeof(int) * 2);
		*fds = malloc(sizeof(int) * 4);
		flags[2] = 5;
	}
	else
	{
		*id = malloc(sizeof(int) * (argc - 3));
		*fds = malloc(sizeof(int) * ((argc - 4)*2 + 2));
		flags[2] = argc;
	}
	
}



/* 
flag0 here_doc
flag1 input file err
flag2 1 argc or 5
 */
int	main(int argc, char *argv[], char *envp[])
{
	pid_t	*id;
	int		*fds;
	int		status;
	int		flags[3];
	int		i;

	i = 0;
	check_args(argc, argv[1], flags, &status);
	init(&id, &fds, flags, argc);
	if (flags[0] == HERE_DOC)
		heredoc(argv[2], &status, &fds[2], &flags[1]);
	else
		fds[(argc - 4)*2] = inopen(argv[1], &status, &flags[1]);
	redir_close(fds[(flags[2] - 4)*2], 0, &status);
	i = flags[1];
	while (i <= flags[2] - 5)
	{
		create_pipe(&fds[2 * i], &status);
		create_child(argv[i + 2 + flags[0]], envp, &fds[2*i], &id[i]);
		if (close(fds[2 * i + 1]) == -1)
			error_handler(ERR, "", &status);
		redir_close(fds[2 * i], 0, &status);
		i++;
	}
	fds[(flags[2] - 4)*2 + 1] = outopen(argv[argc - 1], &status);
	redir_close(fds[(flags[2] - 4)*2 + 1], 1, &status);
	create_child(argv[i + 2 + flags[0]], envp, NULL, &id[flags[2] - 4]);
	wait_end(id, flags, &status, flags[2]);
	free(id);
	free(fds);
	return (WEXITSTATUS(status));
}
