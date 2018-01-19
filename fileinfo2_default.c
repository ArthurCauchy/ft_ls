/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileinfo2_default.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:33:23 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/19 13:43:57 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
		return (NULL);
	else if (!S_ISLNK(file_info->st_mode))
		new->target_path = NULL;
	new->path = input;
	new->mode = mode_to_str(file_info->st_mode);
	new->nlink = file_info->st_nlink;
	new->uid = file_info->st_uid;
	new->gid = file_info->st_gid;
	new->size = file_info->st_size;
	new->blocks = file_info->st_blocks;
	new->mtime = file_info->st_mtim.tv_sec;
	if (new->mode[0] == 'b' || new->mode[0] == 'c')
	{
		new->major = major(file_info->st_rdev);
		new->minor = minor(file_info->st_rdev);
	}
	return (new);
}
