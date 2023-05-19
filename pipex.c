/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:37:48 by mrubina           #+#    #+#             */
/*   Updated: 2023/05/19 01:51:58 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* ./pipex file1 cmd cmd2 file2 
get out1
pipe out1 to cmd2
put out1 to file2
int dup(int fildes); - dublicate fd to the lowest possible fd
int dup2(int fildes, int fildes2); - dublicate fd to another fd
void perror(const char *s);- writes message to stderr
char *strerror(int errnum); returns pointer to the error message
int access(const char *path, int mode); returns 0 if accessable
mode - R_OK, W_OK, X_OK, F_OK - checks if exists
int execve(const char *path, char *const argv[], char *const envp[]); - replaces current program with a program in the path, returns nothing or -1
->int main(int argc, char *argv[], char *envp[])
int pipe(int pipefd[2]); - creates fs - first fd for reading second for writing
void exit(int status) - 
pid_t fork(void); - copies the process returns zero to the child process,  retuns pid of the child process to the parent process
int unlink(const char *pathname); - deletes file if ...
pid_t wait(int *wstatus); waits til the child terminates
pid_t waitpid(pid_t pid, int *wstatus, int options); waits till child changes state
*/

static void write_to_pipe(char *cmd_path, char **cmd_args, char *envp[])
{
	//close(pipefd[0]);
	//close(pipefd[1]);
	//printf("cp %s\n", cmd_path);
	if (execve(cmd_path, cmd_args, envp) == -1) //to out1
		perror("error");
}

static void build_pipe(int *pipefd, char *infile, char *outfile)
{
	//close(pipefd[0]);//close read end
	pipefd[1] = open(infile, O_RDONLY);//open file we read from
	dup2(pipefd[1], 0);//using file as input
	pipefd[0] = open(outfile, O_CREAT | O_WRONLY, 0644);// open file to write into
	dup2(pipefd[0], 1);// output to file
}

void checkLeaks() {
	system("leaks pipex");
}

int	main(int argc, char *argv[], char *envp[])
{
	char **cmd_args;
	char *cmd_path;
	pid_t id1;
	//pid_t id1;
	int pipefd[2];
	int filefd;
	int filefd1;
	int *ex_stat;
	int stat;
	int stat2;
	int *map;
	
	//atexit(checkLeaks);
	*ex_stat = 0;
	//map = rm_char(cmd_path, cmd_path + 8, 't');
	//printf("%i", map[1]);

	if (argc != 5)
		error_handler(6, "", ex_stat);
	//if (access(argv[4], R_OK) == 0)
	//	unlink(argv[4]);
	filefd = open(argv[1], O_RDONLY);
	if (filefd < 0)
	//else
	{
		
		error_handler(ENOENT, argv[1], ex_stat);
		
		filefd = open("/dev/null", O_RDONLY);
	}
	//in = open(find_path(argv[1], envp, R_OK), O_RDONLY);
	if (dup2(filefd, 0)== -1)//using file as input
		error_handler(200, "", ex_stat);
	if (pipe(pipefd) == -1)
		error_handler(1, "", ex_stat);
	id1 = fork();
	//if (id1 != 0)
	//	int_to_file(errno, "ex", 2, 'a');
	
	if (id1 == -1)//child  we write
		error_handler(3, "", ex_stat);	
	else if (id1 == 0)//child  we write
	{
		if (*ex_stat == 2)
			return (1);
		//int_to_file(errno, "ex", 2, 'a');
		//close(filefd);
		close(pipefd[0]);//close read end
		//int_to_file(errno, "ex", 13, 'a');
		cmd_args = get_args(argv[2]);//program name is as input
		//str_to_file(argv[2], "/Users/mrubina/projects/pipex/tt", 1, 'a');
		//str_to_file(cmd_args[0], "/Users/mrubina/projects/pipex/tt", 2, 'a');
		//int_to_file(errno, "ex", 10, 'a');
		cmd_path = find_path(*cmd_args, envp, X_OK);
		//if (ft_strchr(name, '\\') == 0)
		
		dup2(pipefd[1], 1);
		//int_to_file(*ex_stat, "ex", 3, 'a');
		str_to_file(cmd_path, "/Users/mrubina/projects/pipex/tt", 1, 'a');
		if (ft_strchr(cmd_path, '/') == 0 || execve(cmd_path, cmd_args, envp) == -1) //we use in as input output goes to pipefd[1] and to pipefd[0]
			error_handler(300, cmd_path, ex_stat);
		int_to_file(*ex_stat, "ex", 333, 'a');
		return (*ex_stat);
	}
	else//parent we read
	{
		//exit(0);
		//if (id1 != 0)
		//	int_to_file(errno, "ex", 4, 'a');
		close(filefd);
		close(pipefd[1]);
		if (access(argv[4], W_OK) == -1 && errno != ENOENT)
			error_handler(13, argv[4], ex_stat);
		else if (access(argv[4], F_OK) == 0)
			unlink(argv[4]);
		filefd = open(argv[4], O_CREAT | O_WRONLY, 0644);//open file we read from
		if (filefd < 0)
			error_handler(3, "", ex_stat);
		dup2(pipefd[0], 0);
		dup2(filefd, 1);
		id1 = fork();
		if (id1 == -1)//child  we write
			error_handler(3, "", ex_stat);
		else if (id1 == 0)//child  we write
		{
			cmd_args = get_args(argv[3]);//program name is as input
			//str_to_file(cmd_args[1], "/Users/mrubina/projects/pipex/tt", 1, 'a');
			cmd_path = find_path(*cmd_args, envp, X_OK);
			str_to_file(cmd_path, "/Users/mrubina/projects/pipex/tt", 1, 'a');
			//info_to_file(cmd_args, "args");
			if (ft_strchr(cmd_path, '/') == 0 || execve(cmd_path, cmd_args, envp) == -1) //we use in as input output goes to pipefd[1] and to pipefd[0]
				error_handler(300, cmd_path, ex_stat);
			//write_to_pipe(cmd_path, cmd_args, envp);
			//return(0);
			//int_to_file(ex_stat, "ex", 4, 'a');
			//errno = ex_stat;
			//int_to_file(errno, "ex", 5, 'a');
			int_to_file(*ex_stat, "/Users/mrubina/projects/pipex/ex", 222, 'a');
			exit(*ex_stat);
			
		}	
		else//parent we read
		{
			//wait(&stat);
			//wait(&stat);
			//waitpid(id1, &stat, 0);
			waitpid(id1, &stat2, 0);
			
			//close(pipefd[1]);
			//int_to_file(errno, "ex", 4, 'a');
			//waitpid(id1, &stat, 0);
			int_to_file(WEXITSTATUS(stat), "/Users/mrubina/projects/pipex/ex", id1, 'a');
			//waitpid(id1, &stat, 0);
			int_to_file(WEXITSTATUS(stat2), "/Users/mrubina/projects/pipex/ex", id1, 'a');
			//wait(ex_stat);
			//
			close(filefd);
			//if (WIFEXITED(stat))
			return (WEXITSTATUS(stat2));
			//else
			//	return (WEXITSTATUS(stat));
			//int_to_file(*ex_stat, "/Users/mrubina/projects/pipex/ex", 100, 'a');
			//return (0);
		}
		return (0);
	}
	
	return (0);
}
