/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 10:56:10 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/18 14:22:15 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Compare the two files on their
** size value.
*/

int	cmp_s(t_fileinfo *f1, t_fileinfo *f2)
{
	long long	s1;
	long long	s2;

	s1 = (long long)f1->size;
	s2 = (long long)f2->size;
	if (s1 == s2)
		return (cmp_default(f1, f2));
	return (s2 - s1);
}

/*
** Compare the two files on their
** size value. Then reverse it.
*/

int	cmp_sr(t_fileinfo *f1, t_fileinfo *f2)
{
	return (cmp_s(f1, f2) * -1);
}
