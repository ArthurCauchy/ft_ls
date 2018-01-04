/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 13:12:00 by acauchy           #+#    #+#             */
/*   Updated: 2017/12/18 16:29:56 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				load_file(char *input, t_filelist **filelist, t_dirlist **dirlist)
{
	struct stat	stat_info;

	if (lstat(input, &stat_info) < 0)
		return (-1);
	if (S_ISDIR(stat_info.st_mode))
		dirlist_add(dirlist, dirlist_new(input, &stat_info));
	else
		filelist_add(filelist, filelist_new(input, &stat_info));
	return (0);
}

void		read_params(char **argv, t_filelist **filelist, t_dirlist **dirlist, t_errlist **errlist)
{
	int	i;
	int	is_opt;

	i = 1;
	is_opt = 1;
	while (argv[i])
	{
		if (is_opt && !read_option(argv[i]))
		{
			is_opt = 0;
		}
		if (!is_opt)
		{
			if (load_file(argv[i], filelist, dirlist) == -1)
				register_err(argv[i], errlist);
		}
		++i;
	}
}
