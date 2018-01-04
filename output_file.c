#include "ft_ls.h"

/*
** params :
** 1) fileinfo to print
** 2) short name format ? 1 = yes, 0 = no
*/

void	print_file(t_fileinfo *fileinfo, int short_name)
{
	if (option_check('l'))
		print_l_line(fileinfo, short_name);
	else
		print_default(fileinfo, short_name);
}

/*
** params :
** 1) fileinfo to print
** 2) short name format ? 1 = yes, 0 = no
*/

void	print_default(t_fileinfo *fileinfo, int short_name)
{
	if (short_name)
		ft_putendl(get_name_only(fileinfo->path));
	else
		ft_putendl(fileinfo->path);
}
