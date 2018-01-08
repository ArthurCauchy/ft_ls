/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 10:50:46 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/08 14:23:24 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Returns false if the filename specified is either '.' or '..'
*/

static int	is_not_dot(char *filename)
{
	if ((filename[0] == '.' && filename[1] == '\0')
			|| (filename[0] == '.' && filename[1] == '.'
				&& filename[2] == '\0'))
		return (0);
	return (1);
}

static int	explore_dir(char *dirpath, t_filelist **files, t_dirlist **subdirs, int *total_size)
{
	DIR				*dir;
	struct dirent	*file_tmp;
	struct stat		stat_info;
	char			*tmp_name;

	*total_size = 42;// TODO comprendre comment ca marche
	dir = opendir(dirpath);
	if (!dir)
		return (-1);
	while ((file_tmp = readdir(dir)) != NULL)
	{
		if (file_tmp->d_name[0] == '.' && !option_check('a'))
			continue;
		tmp_name = get_filepath(dirpath, file_tmp->d_name);
		if (lstat(tmp_name, &stat_info) < 0)
			return (-1);
		filelist_add(files, filelist_new(tmp_name, &stat_info));
		if (option_check('R') && S_ISDIR(stat_info.st_mode)
				&& is_not_dot(file_tmp->d_name))
			dirlist_add(subdirs, dirlist_new(ft_strdup(tmp_name), &stat_info));
	}
	closedir(dir);
	return (0);
}

void		process_dirs(t_dirlist *dirlist)
{
	t_dirlist	*prev;
	t_dirlist	*subdirs;
	t_filelist	*files;
	int			total_size;

	prev = NULL;
	while (dirlist)
	{
		subdirs = NULL;
		files = NULL;
		total_size = 0;
		if (explore_dir(dirlist->fileinfo->path, &files, &subdirs, &total_size) == -1)
			print_file_error(dirlist->fileinfo->path);
		else
			print_dir(dirlist, files, total_size);
		prev = dirlist;
		dirlist = dirlist->next;
		dirlist_delete(prev);
		process_dirs(subdirs);
	}
}
