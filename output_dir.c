#include "ft_ls.h"

int		explore_dir(char *dirpath, t_filelist **files, t_dirlist **subdirs)
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
		tmp_name = get_filepath(dirpath, file_tmp->d_name);
		if (lstat(tmp_name, &stat_info) < 0)
			return (-1);
		filelist_add(files, filelist_new(tmp_name, &stat_info));
		if (S_ISDIR(stat_info.st_mode))
			dirlist_add(subdirs, dirlist_new(tmp_name, &stat_info));
	}
	return (0);
}

void	print_dir(t_dirlist *dir)
{
	t_filelist	*files;
	t_dirlist		*subdirs;

	files = NULL;
	subdirs = NULL;
	ft_putchar('\n');
	ft_putstr(dir->fileinfo->path);
	ft_putendl(":");
	// TODO print total
	explore_dir(dir->fileinfo->path, &files, &subdirs);
	while (files)
	{
		print_l_line(files->fileinfo, 1);
		files = files->next;
		// TODO free
	}
}
