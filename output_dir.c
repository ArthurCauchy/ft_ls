#include "ft_ls.h"

void	print_dir(t_dirlist *dir, t_filelist *files)
{
	ft_putchar('\n'); // des fois oui des fois non
	ft_putstr(dir->fileinfo->path); // SAUF SI PREMIER ET DERNIER
	ft_putendl(":");
	// TODO print total
	process_files(files, 1);
}
