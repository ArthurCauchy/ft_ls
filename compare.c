#include "ft_ls.h"

int	cmp_default(t_fileinfo *f1, t_fileinfo *f2)
{
	return (ft_strcmp(f1->path, f2->path));
}

int	cmp_r(t_fileinfo *f1, t_fileinfo *f2)
{
	return (cmp_default(f1, f2) * -1);
}

int	cmp_t(t_fileinfo *f1, t_fileinfo *f2)
{
	long long t1;
	long long t2;

	t1 = f1->mtime;
	t2 = f2->mtime;
	return (t2 - t1);
}

int	cmp_tr(t_fileinfo *f1, t_fileinfo *f2)
{
	return (cmp_t(f1, f2) * -1);
}
