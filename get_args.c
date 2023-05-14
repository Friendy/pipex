/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:37:30 by mrubina           #+#    #+#             */
/*   Updated: 2023/05/14 22:10:37 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//returns length including NULL
static int arrlen(char **arr)
{
	int count;

	count = 0;
	while (*arr != NULL)
	{
		count = count + 1;
		arr++;
	}
	return (count + 1);
}

 void cpy_arr(char **src, char **dst)
 {
	if (src != NULL && dst != NULL)
	{
		while (*src != NULL)
		{
			*dst = *src;
			dst++;
			src++;
		}
		*dst = NULL;
	}

 }

static void replace_char(char *str, char *str_end, char old, char new)
{
	while (str != str_end)
	{
		if (*str == old)
			*str = new;
		str++;
	}	
}

void str_rotate(char *str)
{
	while (*str != '\0')
	{
		*str = *(str + 1);
		str++;
	}	
}

static char *quote_trim(char *str)
{
	if (*str == '\'' && *(str + 1) == '"')
		return (ft_strtrim(str, "'"));
	else if (*str == '"' && *(str + 1) == '\'')
	{
		str = ft_strtrim(str, "\"");
		replace_char(str, str + ft_strlen(str), '\'', '"');
		return (str);
	}
	//	return (ft_strtrim(str, "'"));
	else if (*str == '\'')
		return (ft_strtrim(str, "'"));
	else if (*str == '"')
		return (ft_strtrim(str, "\""));
	else
		return (str);
}

void rm_char(char *str, char c)
{
	while (*str != '\0')
	{
		if (*str == c)
			str_rotate(str);
		str++;
	}	
}

static char **split_plus(char *str)
{
	char *start;
	char *end;
	char **args;
	int i;
	int c;
	
	//printf("p %p\n", ft_strchr(str, '"'));
	//printf("p %p\n", ft_strchr(str, '\''));
	if (ft_strchr(str, '"') && ft_strchr(str, '\''))
	{
		if (ft_strchr(str, '"') < ft_strchr(str, '\''))
			c = '"';
		else
			c = '\'';
		//printf("c %c\n", c);
	}
	else if (ft_strchr(str, '"'))
		c = '"';
	else if (ft_strchr(str, '\''))
		c = '\'';
	else
		return (ft_split(str, ' '));
	i = 0;
	start = ft_strchr(str, c) + 1;
	end = ft_strchr(start, c);
	replace_char(start, end, ' ', 9);
	args = ft_split(str, ' ');
	
	while (args[i] != NULL)
	{
		//printf("first %c\n", *(args[i]));
		//printf("first %c\n", c);
		if (*(args[i]) == '\'' || *(args[i]) == '"')
		{
			//rm_char(args[i], 9);
			replace_char(args[i], args[i] + ft_strlen(args[i]) - 1, 9, ' ');
			args[i] = ft_strtrim(args[i], (const char*)&c);
			//args[i] = quote_trim(args[i]);
		}
		i++;
	}
	//arr_info(args);
	return (args);
}

/* static char **split_plus(char *str)
{
	char *start;
	char *end;
	char **args;
	int i;
	int c;
	
	start = NULL;
	//printf("p %p\n", ft_strchr(str, '"'));
	//printf("p %p\n", ft_strchr(str, '\''));
	if (ft_strchr(str, '"') && ft_strchr(str, '\''))
	{
		if (ft_strchr(str, '"') < ft_strchr(str, '\''))
		{
			c = '"';
			start = ft_strchr(str, c);
			end = ft_strchr(start + 1, c);
		}
		else
			c = '\'';
		//printf("c %c\n", c);
	}
	else if (ft_strchr(str, '"'))
		c = '"';
	else if (ft_strchr(str, '\''))
		c = '\'';
	else
		return (ft_split(str, ' '));
	i = 0;
	if (!start)
	{
		start = ft_strchr(str, c) + 1;
		end = ft_strchr(start, c);
	}
	//printf("s %s\n", start);
	replace_char(start, end, ' ', 9);
	args = ft_split(str, ' ');
	
	while (args[i] != NULL)
	{
		//printf("first %c\n", *(args[i]));
		//printf("first %c\n", c);
		if (*(args[i]) == '\'' || *(args[i]) == '"')
		{
			//rm_char(args[i], 9);
			replace_char(args[i], args[i] + ft_strlen(args[i]) - 1, 9, ' ');
			args[i] = ft_strtrim(args[i], (const char*)&c);
			//args[i] = quote_trim(args[i]);
		}
		i++;
	}
	//arr_info(args);
	//info_to_file()
	return (args);
} */


char **get_args(char *arg_str)
{
	char **args;
	char **new_args;
	char len;

	if (arg_str == NULL)
		return (NULL);
	//if (check_input(arg_str))//ft_strchr(arg_str, '\'') || 
		args = split_plus(arg_str);
		//arr_info(args);
	//else
	//	args = ft_split(arg_str, ' ');
	if (args == NULL || *args == NULL)
		return (NULL);
	len = arrlen(args);
	new_args = malloc((len) * sizeof(char *));
	if (new_args == NULL)
		return (NULL);
	cpy_arr(args, new_args);
	new_args[len - 1] = NULL;
	return (new_args);
}
