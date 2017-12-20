#include "ft_ls.h"

int	cmp_default(t_filelist *fl1, t_filelist *fl2)
{
	return (ft_strcmp(fl1->fileinfo->path,
			fl2->fileinfo->path));
}

int	cmp_r(t_filelist *fl1, t_filelist *fl2)
{
	return (cmp_default(fl1, fl2) * -1);
}

int	cmp_t(t_filelist *fl1, t_filelist *fl2)
{
	long long t1;
	long long t2;

	t1 = fl1->fileinfo->mtime;
	t2 = fl2->fileinfo->mtime;
	return (t2 - t1);
}

int	cmp_tr(t_filelist *fl1, t_filelist *fl2)
{
	return (cmp_t(fl1, fl2) * -1);
}
