/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileinfo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:33:23 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/08 10:26:05 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		get_filetype(mode_t file_mode)
{
	if (S_ISREG(file_mode))
		return ('-');
	else if (S_ISCHR(file_mode))
		return ('c');
	else if (S_ISBLK(file_mode))
		return ('b');
	else if (S_ISBLK(file_mode))
		return ('b');
	else if (S_ISDIR(file_mode))
		return ('d');
	else if (S_ISFIFO(file_mode))
		return ('p');
	else if (S_ISLNK(file_mode))
		return ('l');
	else if (S_ISSOCK(file_mode))
		return ('s');
	else
		return ('u');
}

static char		*mode_to_str(mode_t file_mode)
{
	char	*str;

	if (!(str = (char*)malloc(11)))
		return (NULL);
	str[0] = get_filetype(file_mode);
	str[1] = file_mode & S_IRUSR ? 'r' : '-';
	str[2] = file_mode & S_IWUSR ? 'w' : '-';
	str[3] = file_mode & S_IXUSR ? 'x' : '-';
	if (file_mode & S_ISUID)
		str[3] = str[3] == 'x' ? 's' : 'S';
	str[4] = file_mode & S_IRGRP ? 'r' : '-';
	str[5] = file_mode & S_IWGRP ? 'w' : '-';
	str[6] = file_mode & S_IXGRP ? 'x' : '-';
	if (file_mode & S_ISGID)
		str[6] = str[6] == 'x' ? 's' : 'S';
	str[7] = file_mode & S_IROTH ? 'r' : '-';
	str[8] = file_mode & S_IWOTH ? 'w' : '-';
	str[9] = file_mode & S_IXOTH ? 'x' : '-';
	if (file_mode & S_ISVTX)
		str[9] = str[9] == 'x' ? 't' : 'T';
	str[10] = '\0';
	return (str);
}

static char		*symlink_target_path(char *link_path, off_t file_size)
{
	size_t	buffer_size;
	char	*target_path;
	ssize_t	read_size;

	buffer_size = (file_size > 0 ? file_size : PATH_MAX) + 1;
	if (!(target_path = (char*)malloc(buffer_size)))
		return (NULL);
	read_size = readlink(link_path, target_path, buffer_size);
	if (read_size < 0)
		return (NULL);
	target_path[read_size] = '\0';
	return (target_path);
}

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
	new->mtime = file_info->st_mtimespec.tv_sec;
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

void			fileinfo_delete(t_fileinfo *fileinfo)
{
	free(fileinfo->path);
	free(fileinfo->mode);
	free(fileinfo->target_path);
	free(fileinfo);
}
