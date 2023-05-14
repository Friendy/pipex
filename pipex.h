/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:19:40 by mrubina           #+#    #+#             */
/*   Updated: 2023/05/14 17:02:50 by mrubina          ###   ########.fr       */
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
char	*find_path(char *cand_path, char *envp[], int t);
char	**get_args(char *arg_str);
void cpy_arr(char **src, char **dst);
void arr_info(char **arr);
void free_arr(char **arr);
void pipe_info(int *pipefd);
void str_rotate(char *str);
void rm_char(char *str, char c);
void info_to_file(char **arr, char  *file);
void get_var(char *var_name, char *file, int flag);
#endif
