/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:19:40 by mrubina           #+#    #+#             */
/*   Updated: 2023/05/18 18:23:36 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <string.h>
# include <malloc/malloc.h>
char *replace_char(char *str, char *str_end, char old_c, char new_c);
void replace_by_map(char *str, char *map, char c);
void arr_info(char **arr);
void free_arr(char **arr);
void pipe_info(int *pipefd);
void info_to_file(char **arr, char  *file);
void get_var(char *var_name, char *file, int flag);
void int_to_file(int i, char *file, int id, int flag);
void str_to_file(char *str, char *file, int id, int flag);
#endif
