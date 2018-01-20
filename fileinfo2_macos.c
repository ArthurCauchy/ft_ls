/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileinfo2_macos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:33:23 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/20 10:52:14 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Fill a fileinfo structure with basic data from a
** struct stat.
*/

static void		fill_fileinfo(t_fileinfo *fileinfo, struct stat *file_info)
{
	fileinfo->mode = mode_to_str(file_info->st_mode);
	fileinfo->nlink = file_info->st_nlink;
	fileinfo->uid = file_info->st_uid;
	fileinfo->gid = file_info->st_gid;
	fileinfo->size = file_info->st_size;
	fileinfo->blocks = file_info->st_blocks;
	fileinfo->mtime = file_info->st_mtimespec.tv_sec;
	if (fileinfo->mode[0] == 'b' || fileinfo->mode[0] == 'c')
	{
		fileinfo->major = major(file_info->st_rdev);
		fileinfo->minor = minor(file_info->st_rdev);
	}
}

/*
** Creates a new fileinfo element.
**
** params :
** 1) path/name of the file
** 2) a stat struct returned by stat() or lstat()
**
** return :
** The created fileinfo element, or NULL if it failed.
*/

t_fileinfo		*fileinfo_new(char *input, struct stat *file_info)
{
	t_fileinfo	*new;

	if (!(new = (t_fileinfo*)malloc(sizeof(t_fileinfo))))
		return (NULL);
	if (S_ISLNK(file_info->st_mode) &&
		!(new->target_path = symlink_target_path(input, file_info->st_size)))
	{
		free(new);
		return (NULL);
	}
	else if (!S_ISLNK(file_info->st_mode))
		new->target_path = NULL;
	new->path = input;
	fill_fileinfo(new, file_info);
	return (new);
}
