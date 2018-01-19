/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 10:50:46 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/19 13:31:57 by arthur           ###   ########.fr       */
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

/*
** Creates a fileinfo struct from lstat call,
** then creates a filelist (and a dirlist structure sometimes).
*/

static int	explore_dir_files(char *dirname, char *filename,
		t_filelist **files, t_dirlist **subdirs)
{
	struct stat	stat_info;
	t_filelist	*new_file;

	if (lstat(filename, &stat_info) == -1)
	{
		print_file_error(filename);
		return (-1);
	}
	if (!(new_file = filelist_new(filename, &stat_info)))
		return (-1);
	filelist_add(files, new_file);
	if (option_check('R') && S_ISDIR(stat_info.st_mode)
			&& is_not_dot(dirname))
		dirlist_add(subdirs, dirlist_new(ft_strdup(filename), &stat_info));
	return (0);
}

/*
** Explore files in a directory and add them to a 'files' filelist struct.
** If 'R' option is specified in g_options global,
** also add them to a 'subdirs' dirlist struct.
**
** params :
** 1) path of the directory to explore
** 2) list of files found
** 3) list of subdirs found
**
** return :
** 0 = success, -1 = impossible to open the dir
*/

static int	explore_dir(char *dirpath, t_filelist **files, t_dirlist **subdirs)
{
	DIR				*dir;
	struct dirent	*file_tmp;
	char			*tmp_name;

	dir = opendir(dirpath);
	if (!dir)
		return (-1);
	while ((file_tmp = readdir(dir)) != NULL)
	{
		if (file_tmp->d_name[0] == '.' && !option_check('a'))
			continue ;
		tmp_name = get_filepath(dirpath, file_tmp->d_name);
		if (explore_dir_files(file_tmp->d_name, tmp_name, files, subdirs) == -1)
		{
			free(tmp_name);
			g_retcode = EXIT_FAILURE;
			continue ;
		}
	}
	closedir(dir);
	return (0);
}

/*
** Explore a given directory and print it's files or an error.
*/

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

/*
** Process every directories of a dirlist :
** explore them, print their content or an error.
**
** This is a recursive function if 'R' option is set in g_options global.
*/

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
