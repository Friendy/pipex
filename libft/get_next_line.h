/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:20:18 by mrubina           #+#    #+#             */
/*   Updated: 2023/04/26 18:29:33 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

# include <unistd.h>
# include <stdlib.h>

char	*read_next_line(int fd, char **p_buf);
int		cpy_til_nl(int last_rd, char *buf, char *temp);
char	*buf_diff(char *small, char *big, int last_ind);
char	*resize(char *buf, int last_ind);
char	*free_bufs(char **buf1, char **buf2);
char	*init_params(int fd, char *buf, int *curr, ssize_t *rd);
char	**free_arr(char **arr, int last_ind);
#endif
