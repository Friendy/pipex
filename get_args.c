/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:37:30 by mrubina           #+#    #+#             */
/*   Updated: 2023/05/18 18:24:41 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char get_quote(char *str)
{
	if (ft_strchr(str, '"') && ft_strchr(str, '\''))
	{
		if (ft_strchr(str, '"') < ft_strchr(str, '\''))
			return ('"');
		else
			return ('\'');
	}
	else if (ft_strchr(str, '"'))
		return ('"');
	else if (ft_strchr(str, '\''))
		return ('\'');
	else
		return ('0');
}

static char *last_quote(char *str, char c)
{
	if (c == '\'')
		return (ft_strchr(str, c));
	while (str && *str != '\0')
	{
		if ((str - 1) && *str == '"' && *(str - 1) != '\\')
			return (str);
		str++;
	}
	return (str - 1);
}

static char **split_plus(char *str)
{
	char *start;
	char **args;
	int i;
	int c;
	char *map;
	
	c = get_quote(str);
	if (c == '0')
		return (ft_split(str, ' '));
	i = 0;
	start = ft_strchr(str, c) + 1;
	map = replace_char(start, last_quote(start, c), ' ', 9);
	args = ft_split(str, ' ');
	while (args[i] != NULL)
	{
		if (*(args[i]) == '\'' || *(args[i]) == '"')
		{
			replace_by_map(args[i] + 1, map, ' ');
			args[i] = ft_strtrim(args[i], (const char*)&c);
		}
		i++;
	}
	return (args);
}

char **get_args(char *arg_str)
{
	char **args;
	char len;

	if (arg_str == NULL)
		return (NULL);
	if (arg_str[0] == '.' && arg_str[1] == '/')
	{
		args = malloc(2 * sizeof(char *));
		args[0] = arg_str;
		args[1] = NULL;
		return (args);
	}
	args = split_plus(arg_str);
	if (args == NULL || *args == NULL)
		return (NULL);
	return (args);
}
