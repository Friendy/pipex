/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:37:30 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/04 17:27:54 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	get_quote(char *str)
{
	if (str == NULL)
		return ('0');
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

static char	*last_quote(char *str, char c)
{
	if (str == NULL)
		return (str);
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

static char	*trim_replace(char *str, char c)
{
	char	*new_str;

	new_str = ft_strtrim(str, (const char *)&c);
	free_str(str);
	return (new_str);
}

static char	**split_plus(char *str)
{
	char	*start;
	char	**args;
	int		i;
	int		c;
	char	*map;

	c = get_quote(str);
	if (c == '0')
		return (ft_split(str, ' '));
	start = ft_strchr(str, c) + 1;
	map = replace_char(start, last_quote(start, c), ' ', 9);
	args = ft_split(str, ' ');
	i = 0;
	while (args[i] != NULL)
	{
		if (*(args[i]) == '\'' || *(args[i]) == '"')
		{
			replace_by_map(args[i] + 1, map, ' ');
			args[i] = trim_replace(args[i], c);
		}
		i++;
	}
	free_str(map);
	return (args);
}

char	**get_args(char *arg_s)
{
	char	**args;

	if (arg_s == NULL)
		return (NULL);
/* 	if (arg_s && ft_strlen(arg_s) >= 2 && arg_s[0] == '.' && arg_s[1] == '/')
	{
		args = malloc(2 * sizeof(char *));
		args[0] = arg_s;
		args[1] = NULL;
		return (args);
	} */
	args = split_plus(arg_s);
	return (args);
}
