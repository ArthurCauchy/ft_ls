/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 10:50:46 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/18 13:50:01 by acauchy          ###   ########.fr       */
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

static int	explore_dir(char *dirpath, t_filelist **files, t_dirlist **subdirs)
{
	DIR				*dir;
	struct dirent	*file_tmp;
	struct stat		stat_info;
	char			*tmp_name;

	dir = opendir(dirpath);
	if (!dir)
		return (-1);
	while ((file_tmp = readdir(dir)) != NULL)
	{
		if (file_tmp->d_name[0] == '.' && !option_check('a'))
			continue;
		tmp_name = get_filepath(dirpath, file_tmp->d_name);
		if (lstat(tmp_name, &stat_info) < 0)
		{
			free(tmp_name);
			continue ;
		}
		filelist_add(files, filelist_new(tmp_name, &stat_info));
		if (option_check('R') && S_ISDIR(stat_info.st_mode)
				&& is_not_dot(file_tmp->d_name))
			dirlist_add(subdirs, dirlist_new(ft_strdup(tmp_name), &stat_info));
	}
	closedir(dir);
	return (0);
}

static void	process_one_dir(t_dirlist *dirlist, t_dirlist **subdirs,
		t_filelist **files, int is_first)
{
	*subdirs = NULL;
	*files = NULL;
	if (explore_dir(dirlist->fileinfo->path, files, subdirs) == -1)
	{
		g_retcode = EXIT_FAILURE;
		print_file_error(dirlist->fileinfo->path);
	}
	else
		print_dir(dirlist, *files, is_first);
}

void		process_dirs(t_dirlist *dirlist,
		t_filelist *filelist, t_errlist *errlist)
{
	t_dirlist	*prev;
	t_dirlist	*subdirs;
	t_filelist	*files;

	prev = NULL;
	while (dirlist)
	{
		if (prev == NULL)
		{
			if (!filelist && !errlist && dirlist->next == NULL)
				process_one_dir(dirlist, &subdirs, &files, 2);
			else
				process_one_dir(dirlist, &subdirs, &files, 1);
		}
		else
			process_one_dir(dirlist, &subdirs, &files, 0);
		prev = dirlist;
		dirlist = dirlist->next;
		dirlist_delete(prev);
		if (subdirs)
		{
			ft_putchar('\n');
			process_dirs(subdirs, filelist, errlist);
		}
	}
}
