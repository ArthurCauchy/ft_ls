#include "ft_ls.h"

void	process_inputs(t_filelist *filelist, t_dirlist *dirlist)
{
	process_files(filelist, 0);
	process_dirs(dirlist);
}

/*
** Process the files given (print and free actually)
** params :
** 1) filelist : files to print
** 2) short name format ? 1 = yes, 0 = no
*/

void	process_files(t_filelist *filelist, int short_name)
{
	t_filelist	*prev;

	prev = NULL;
	while (filelist)
	{
		print_file(filelist->fileinfo, short_name);
		prev = filelist;
		filelist = filelist->next;
		filelist_delete(prev);
	}
}
