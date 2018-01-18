/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileinfo2_default.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:33:23 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/18 13:10:43 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_fileinfo		*fileinfo_new(char *input, struct stat *file_info)
{
	t_fileinfo	*new;

	if (!(new = (t_fileinfo*)malloc(sizeof(t_fileinfo))))
		return (NULL);
	new->path = input;
	new->mode = mode_to_str(file_info->st_mode);
	new->nlink = file_info->st_nlink;
	new->uid = file_info->st_uid;
	new->gid = file_info->st_gid;
	new->size = file_info->st_size;
	new->blocks = file_info->st_blocks;
	new->mtime = file_info->st_mtim.tv_sec;
	if (new->mode[0] == 'l')
		new->target_path = symlink_target_path(new->path, new->size);
	else
		new->target_path = NULL;
	if (new->mode[0] == 'b' || new->mode[0] == 'c')
	{
		new->major = major(file_info->st_rdev);
		new->minor = minor(file_info->st_rdev);
	}
	return (new);
}
