/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:19:40 by mrubina           #+#    #+#             */
/*   Updated: 2023/05/18 19:35:21 by mrubina          ###   ########.fr       */
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
# include "utils.h"
#include <sys/types.h>
#include <sys/wait.h>
char	*find_path(char *cand_path, char *envp[], int t);
char	**get_args(char *arg_str);
void str_rotate(char *str);
void str_rotate1(char *str, char *str_end);
void error_handler(int type, char *name, int *exit_stat);
int *rm_char(char *str, char *str_end, char c);
#endif
