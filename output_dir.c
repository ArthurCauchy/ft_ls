#include "ft_ls.h"

int		explore_dir(char *options, char *dirpath, t_filelist **files, t_dirlist **subdirs)
{
	DIR						*dir;
	struct dirent	*subd;
	struct stat		stat_info;
	char					*tmp_name;

	dir = opendir(dirpath);
	if (!dir)
		return (-1);
	while ((subd = readdir(dir)) != NULL)
	{
		tmp_name = get_filepath(dirpath, subd->d_name);
		if (lstat(tmp_name, &stat_info) < 0)
			return (-1);
		filelist_add(options, files, filelist_new(tmp_name, &stat_info));
		if (S_ISDIR(stat_info.st_mode))
			dirlist_add(options, subdirs, dirlist_new(tmp_name, &stat_info));
		free(tmp_name);
	}
	return (0);
}

void	print_dir(char *options, t_dirlist *dir)
{
	t_filelist	*files;
	t_dirlist		*subdirs;

	ft_putstr(dir->fileinfo->path);
	ft_putendl(":");
	// TODO print total
	explore_dir(options, dir->fileinfo->path, &files, &subdirs);
	while (files)
	{
		print_l_line(files->fileinfo, 1);
		files = files->next;
		// TODO free
	}
}
