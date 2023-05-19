/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:37:30 by mrubina           #+#    #+#             */
/*   Updated: 2023/05/19 01:52:23 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* "/dir1/dir2:/dir3/dir4:..." - path_str
	"dir3/dir4/file" - path */
static char	*extract_path(char *path_str, char *name)
{
	int access_given;
	char **path_arr;
	char *path_cand;

	path_arr = ft_split(path_str, ':');
	access_given = -1;
	while (*path_arr != NULL && access_given == -1)
	{
		path_cand = ft_strjoin(*path_arr, ft_strjoin("/", name));
		access_given = access(path_cand, X_OK);
		path_arr++;
	}
	if (access_given == 0)
		return (path_cand);
	//else if (ft_strchr(name))
	return (name);
	//else
	//{	error_handler(300, name, 0);
	//	exit(1);}
		//return (name);	
}

/* cand_path is "/dir1/dir2/file" 
	or "file" */
char	*find_path(char *cand_path, char *envp[], int flag)
{
	int n;
	int i;
	char *path_str;
	
	//if (access(cand_path, flag) == -1 && errno != ENOENT)
	//		error_handler(13, cand_path, 0);
	//else
	if (access(cand_path, flag) == 0 && cand_path[0] == '.' && cand_path[1] == '/')
		return (cand_path);
	n = 1;
	i = 0;
	while (envp[i] != NULL && n != 0)
	{
		n = ft_strncmp(envp[i], "PATH=", 5);
		if (n != 0)
			i++;
	}
	//path_str = ft_strdup(&((envp[i])[5]));
	return (extract_path(&((envp[i])[5]), cand_path));	
}
