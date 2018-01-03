#include "ft_ls.h"

/*
** params :
** 1) fileinfo to print
** 2) short name format ? 1 = yes, 0 = no
*/

void	print_l_line(t_fileinfo *fileinfo, int short_name)
{
	ft_miniprint("%r0s% ", fileinfo->mode);
	ft_miniprint("%r4d% ", &fileinfo->nlink);
	if (getpwuid(fileinfo->uid))
		ft_miniprint("%r12s% ", getpwuid(fileinfo->uid)->pw_name);
	else
		ft_miniprint("%r12d% ", &fileinfo->uid);
	if (getgrgid(fileinfo->gid))
		ft_miniprint("%r12s% ", getgrgid(fileinfo->gid)->gr_name);
	else
		ft_miniprint("%r12d% ", &fileinfo->gid);
	if (fileinfo->mode[0] == 'b' || fileinfo->mode[0] == 'c')
		ft_miniprint("%r3d%, %r3d%", &fileinfo->major, &fileinfo->minor);
	else
		ft_miniprint("%r8d% ", &fileinfo->size);
	ft_miniprint("%r0d% ", &fileinfo->mtime); // faire une fct de conversion (ou affichage direct) 
	ft_miniprint("%r0s%\n",
			(short_name) ? get_name_only(fileinfo->path) : fileinfo->path);
}
