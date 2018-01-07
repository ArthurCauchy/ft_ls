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
**
** pos will be used to know if it's the first, middle or last element
** -1 = first, 0 = middle, 1 = last
*/

void	process_files(t_filelist *filelist, int short_name)
{
	t_filelist	*prev;
	int			pos;

	prev = NULL;
	pos = -1;
	while (filelist)
	{
		prev = filelist;
		filelist = filelist->next;
		if (filelist)
			print_file(prev->fileinfo, short_name, pos);
		else
			print_file(prev->fileinfo, short_name, 1);
		filelist_delete(prev);
		pos = 0;
	}
}
