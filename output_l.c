/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 10:55:47 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/11 18:33:40 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** params :
** 1) fileinfo to print
** 2) short name format ? 1 = yes, 0 = no
**
** NOTE: This function do not print anything until pos is equal to 2 (last)
*/

void	print_l_line(t_fileinfo *fileinfo, int short_name, int pos)
{
	static int		*col_sizes;
	static t_list	*lprintlist = NULL;
	t_lprint		*lp_new;

	if (pos == 1 || pos == 2)
	{
		ft_lstiter(lprintlist, &lprint_print);
		ft_lstdel(&lprintlist, &lprint_delete);
		free(col_sizes);
		col_sizes = NULL;
	}
	else
	{
		if (!col_sizes)
			col_sizes = ft_memalloc(4 * sizeof(int));
		lp_new = lprint_new(fileinfo, short_name);
		ft_lstpushback(&lprintlist, ft_lstnew((void*)lp_new, sizeof(t_lprint)));
		//update_cols(col_sizes, lp_new);
	}
}
