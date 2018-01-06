#include "ft_ls.h"

static int	explore_dir(char *dirpath, t_filelist **files, t_dirlist **subdirs)
{
	DIR						*dir;
	struct dirent	*file_tmp;
	struct stat		stat_info;
	char					*tmp_name;

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
		if (option_check('R') && S_ISDIR(stat_info.st_mode))
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

	prev = NULL;
	while (dirlist)
	{
		subdirs = NULL;
		files = NULL;
		if (explore_dir(dirlist->fileinfo->path, &files, &subdirs) == -1)
			print_file_error(dirlist->fileinfo->path);
		else
			print_dir(dirlist, files);
		prev = dirlist;
		dirlist = dirlist->next;
		dirlist_delete(prev);
		process_dirs(subdirs);
	}
}
