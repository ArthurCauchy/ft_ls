#include "ft_ls.h"

/*void	print_l_line(t_filelist *filelist)
{
	t_fileinfo *info;

	info = filelist->fileinfo;
	ft_putstr(info->mode);
	ft_putchar(' ');
	ft_putnbr(info->nlink);
	ft_putchar(' ');
	if (getpwuid(info->uid))
		ft_putstr(getpwuid(info->uid)->pw_name);
	else
		ft_putnbr(info->uid);
	ft_putchar(' ');
	if (getgrgid(info->gid))
		ft_putstr(getgrgid(info->gid)->gr_name);
	else
		ft_putnbr(info->gid);
	ft_putchar(' ');
	if (info->mode[0] == 'b' || info->mode[0] == 'c')
	{
		ft_putnbr(info->major);
		ft_putstr(", ");
		ft_putnbr(info->minor);
	}
	else
		ft_putnbr(info->size);
	ft_putchar(' ');
	ft_putnbr(info->mtime); // faire une fct de conversion (ou affichage direct) !
	ft_putchar(' ');
	ft_putendl(info->path);
}*/

void	print_l_line(t_filelist *filelist)
{
	t_fileinfo *info;

	info = filelist->fileinfo;
	ft_miniprint("%r0s% ", info->mode);
	ft_miniprint("%r4d% ", &info->nlink);
	if (getpwuid(info->uid))
		ft_miniprint("%r12s% ", getpwuid(info->uid)->pw_name);
	else
		ft_miniprint("%r12d% ", &info->uid);
	if (getgrgid(info->gid))
		ft_miniprint("%r12s% ", getgrgid(info->gid)->gr_name);
	else
		ft_miniprint("%r12d% ", &info->gid);
	if (info->mode[0] == 'b' || info->mode[0] == 'c')
		ft_miniprint("%r3d%, %r3d%", &info->major, &info->minor);
	else
		ft_miniprint("%r8d% ", &info->size);
	ft_miniprint("%r0d% ", &info->mtime); // faire une fct de conversion (ou affichage direct) !
	ft_miniprint("%r0s%\n", info->path);
}
