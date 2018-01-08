/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 16:41:56 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/08 11:00:54 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	exit_error(void)
{
	print_error(NULL);
	exit(EXIT_FAILURE);
}

char	*get_name_only(char *path)
{
	char	*name_start;
	int		tmp;

	name_start = path;
	tmp = 0;
	while (*path)
	{
		if (tmp == 1)
		{
			name_start = path;
			tmp = 0;
		}
		else if (*path == '/')
			tmp = 1;
		++path;
	}
	return (name_start);
}

char	*get_filepath(char *dirpath, char *filename)
{
	static char	filepath[MAX_PATH_SIZE];
	size_t		i;

	i = 0;
	while (*dirpath)
	{
		filepath[i] = *dirpath;
		++dirpath;
		++i;
	}
	filepath[i] = '/';
	++i;
	while (*filename)
	{
		filepath[i] = *filename;
		++filename;
		++i;
	}
	filepath[i] = '\0';
	return (ft_strdup(filepath));
}
