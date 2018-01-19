/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 16:41:56 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/18 18:50:11 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Print the given error message by calling print_error, then exit.
*/

void	exit_error(char *msg)
{
	print_error(msg);
	exit(EXIT_FAILURE);
}

/*
** Returns the filename contained in the given file path.
**
** No new string is actually created,
** a pointer to the character starting the filename is returned.
*/

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

/*
** Given a directory path and the filename of a file in this directory,
** generate a new string containing the filepath.
*/

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
	if (filepath[i - 1] != '/')
		filepath[i++] = '/';
	while (*filename)
	{
		filepath[i] = *filename;
		++filename;
		++i;
	}
	filepath[i] = '\0';
	return (ft_strdup(filepath));
}

/*
** Convert time_t stamp to a 10 characters human-readable string.
** The conversion is done the same way ls does it.
** If the date is more than 6 month later or before,
** year is shown instead of hours:minutes.
*/

char	*time_to_str(time_t file_time)
{
	time_t	current_time;
	char	*ctime_str;
	char	*final;
	int		i;
	int		j;

	current_time = time(NULL);
	ctime_str = ctime(&file_time);
	if (file_time > current_time - 15768000
			&& file_time < current_time + 15768000)
		final = ft_strsub(ctime_str, 4, 12);
	else
	{
		i = 4;
		j = 0;
		final = ft_strnew(12);
		while (i < 11)
			final[j++] = ctime_str[i++];
		i = 19;
		while (i < 24)
			final[j++] = ctime_str[i++];
	}
	return (final);
}
