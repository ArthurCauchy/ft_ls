/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 10:56:10 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/18 14:20:30 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Compare the two files on their
** filepath's ASCII values.
*/

int	cmp_default(t_fileinfo *f1, t_fileinfo *f2)
{
	return (ft_strcmp(f1->path, f2->path));
}

/*
** Compare the two files on their
** filepath's ASCII values. Then reverse it.
*/

int	cmp_r(t_fileinfo *f1, t_fileinfo *f2)
{
	return (cmp_default(f1, f2) * -1);
}

/*
** Compare the two files on their
** modified time value.
*/

int	cmp_t(t_fileinfo *f1, t_fileinfo *f2)
{
	long long t1;
	long long t2;

	t1 = f1->mtime;
	t2 = f2->mtime;
	if (t1 == t2)
		return (cmp_default(f1, f2));
	return (t2 - t1);
}

/*
** Compare the two files on their
** modified time value. Then reverse it.
*/

int	cmp_tr(t_fileinfo *f1, t_fileinfo *f2)
{
	return (cmp_t(f1, f2) * -1);
}
