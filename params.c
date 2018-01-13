/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 13:12:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/13 13:50:02 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*delete_dir_slash(char *input)
{
	char	*new;
	size_t	i;

	new = ft_strdup(input);
	i = ft_strlen(new) - 1;
	while (i > 0 && new[i] == '/')
		--i;
	new[i + 1] = '\0';
	return (new);
}

int			load_file(char *input, t_filelist **filelist, t_dirlist **dirlist)
{
	struct stat	stat_info;

	if ((option_check('l') && lstat(input, &stat_info) < 0)
			|| (stat(input, &stat_info) < 0))
		return (-1);
	if (S_ISDIR(stat_info.st_mode) && !option_check('d'))
		dirlist_add(dirlist, dirlist_new(delete_dir_slash(input), &stat_info));
	else
		filelist_add(filelist, filelist_new(ft_strdup(input), &stat_info));
	return (0);
}

void		read_params(char **argv, t_filelist **filelist,
		t_dirlist **dirlist, t_errlist **errlist)
{
	int	i;
	int	is_opt;

	i = 1;
	is_opt = 1;
	while (argv[i])
	{
		if (is_opt && !read_option(argv[i]))
			is_opt = 0;
		if (!is_opt)
			if (load_file(argv[i], filelist, dirlist) == -1)
				register_err(argv[i], errlist);
		++i;
	}
	if (!*filelist && !*dirlist && !*errlist)
	{
		if (load_file(".", filelist, dirlist) == -1)
			register_err(".", errlist);
	}
}
