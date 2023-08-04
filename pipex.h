/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:19:40 by mrubina           #+#    #+#             */
/*   Updated: 2023/08/04 21:51:53 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <errno.h>
# include <string.h>
# include <malloc/malloc.h>
# include <sys/types.h>
# include <sys/wait.h>

# define ERR 100
# define ARG 6
# define NFOUND 300
# define NFOUNDEX 400
# define EACCES1 14
# define NULLPATH 15
# define EACCES1 14

char	*find_path(char *cand_path, char *envp[], int *status);
char	**get_args(char *arg_str);
char	*replace_char(char *str, char *str_end, char old_c, char new_c);
void	replace_by_map(char *str, char *map, char c);
void	free_arr(char **arr);
void	error_handler(int type, char *name, int *exit_stat);
char	*extract_path(char *path_str, char *name);
void	free_str(char *s);
#endif
