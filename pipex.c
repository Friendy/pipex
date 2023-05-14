/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:37:48 by mrubina           #+#    #+#             */
/*   Updated: 2023/05/14 18:58:34 by mrubina          ###   ########.fr       */
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

static void error_handler(int type, char *name)
{
	if (type == 6)
		ft_printf("Error: wrong number of arguments");
	if (type == ENOENT)
	{	perror(ft_strjoin("./pipex: ", name));
	//perror("No access to the file ");
	//ft_printf("%s: %s: %s\n", "./pipex", strerror(type), name);
	}
		//ft_printf("%s", name);}
		//perror("No access to the file ");
	if (type == 1)
		perror("Could not create pipe");
	if (type == 3)
		perror("Could not duplicate process");
	if (type == 127)
		perror(strerror(127));
		//perror(ft_strjoin("Could not execute ", name));	
	exit(type);
}
/* static void error_handler(int type, char *name)
{
	if (type == 6)
		ft_printf("Error: wrong number of arguments");
	if (type == 1)
		perror("");
	if (type == 2)
		perror("");
	if (type == 3)
		perror("");
	if (type == 4)
		perror("");
	exit(1);
} */

int	main(int argc, char *argv[], char *envp[])
{
	int	i;
	char **cmd_args;
	char *cmd_path;
	pid_t id1;
	int pipefd[2];
	int in;
	int out;
	char *buf;
	
	i = 0;
	//strerror(127)
	//buf = ft_strdup("tesl t tytyt tyt");
	//rm_char(buf, ' ');
	//printf("%s\n", strerror(2));
	//2 - no file or dir
	//exit(0);
	//arr_info(argv);
	//info_to_file(envp, "env_info");
	if (argc != 5)
		error_handler(6, "");
	if (access(argv[4], R_OK) == 0)
		unlink(argv[4]);
	
	//arr_info(envp);
	
		//
		
	//printf("ttt");
	if (access(argv[1], R_OK) == 0)
		in = open(argv[1], O_RDONLY);
	else
		error_handler(ENOENT, argv[1]);
	//in = open(find_path(argv[1], envp, R_OK), O_RDONLY);
	i = dup2(in, 0);//using file as input
	if (pipe(pipefd) == -1)
		error_handler(1, "");
	id1 = fork();
	if (id1 == -1)//child  we write
		error_handler(3, "");
	else if (id1 == 0)//child  we write
	{
		//arr_info(envp);
		//printf("end");
		close(pipefd[0]);//close read end
		cmd_args = get_args(argv[2]);//program name is as input
		cmd_path = find_path(*cmd_args, envp, X_OK);
		i = dup2(pipefd[1], 1);
		
		
		
			//if (access(find_path(argv[1], envp), R_OK) != 0)
			//error_handler(ENOENT, argv[1]);
		//get_var("VAR1", "vars", 1);
		//get_var("VAR2", "vars", 'a');	
		//cmd_args	
			//ft_printf("%s: %s: %s\n", "./pipex", strerror(ENOENT), argv[1]);
		if (execve(cmd_path, cmd_args, envp) == -1) //we use in as input output goes to pipefd[1] and to pipefd[0]
			error_handler(127, cmd_path);
		return (0);
	}	
	else//parent we read
	{
		close(in);
		close(pipefd[1]);
		//i = wait(0);
		
		out = open(argv[4], O_CREAT | O_WRONLY, 0644);//open file we read from
	
		//free(cmd_path);
		//free(cmd_args);
	
		//unlink(argv[4]);
		
		//i = dup2(pipefd[1], 1); // write output to pipe
		
		i = dup2(pipefd[0], 0);
		i = dup2(out, 1);
		id1 = fork();
		if (id1 == -1)//child  we write
			error_handler(3, "");
		else if (id1 == 0)//child  we write
		{
			cmd_args = get_args(argv[3]);//program name is as input
			cmd_path = find_path(*cmd_args, envp, X_OK);
			info_to_file(cmd_args, "args");
			if (execve(cmd_path, cmd_args, envp) == -1) //we use in as input output goes to pipefd[1] and to pipefd[0]
				error_handler(4, cmd_path);
			//write_to_pipe(cmd_path, cmd_args, envp);
			//return(0);
		}	
		else//parent we read
		{
			close(pipefd[1]);
			i = wait(0);
			close(out);
			return (0);
		}
		return (0);
	}
	return (0);
}
