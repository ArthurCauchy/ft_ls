/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 10:56:10 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/15 13:39:59 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	cmp_S(t_fileinfo *f1, t_fileinfo *f2)
{
	long long	s1;
	long long	s2;

	s1 = (long long)f1->size;
	s2 = (long long)f2->size;
	if (s1 == s2)
		return (cmp_default(f1, f2));
	return (s2 - s1);
}

int	cmp_Sr(t_fileinfo *f1, t_fileinfo *f2)
{
	return (cmp_S(f1, f2) * -1);
}
