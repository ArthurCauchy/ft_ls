/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 10:55:47 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/18 19:52:10 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Read the col sizes of an lprint struct element,
** then updates col_sizes accordingly.
*/

static void	read_col_sizes(int *col_sizes, t_lprint *lp)
{
	int	len_nlink;
	int	len_uid;
	int	len_gid;
	int	len_size;

	len_nlink = ft_strlen(lp->nlink);
	len_uid = ft_strlen(lp->uid);
	len_gid = ft_strlen(lp->gid);
	len_size = ft_strlen(lp->size);
	if (len_nlink > col_sizes[0])
		col_sizes[0] = len_nlink;
	if (len_uid > col_sizes[1])
		col_sizes[1] = len_uid;
	if (len_gid > col_sizes[2])
		col_sizes[2] = len_gid;
	if (len_size > col_sizes[3])
		col_sizes[3] = len_size;
}

/*
** Ajust sizes of every elements of every lprint in the list
** to match col_sizes sizes.
** Performed just before printing.
*/

static void	apply_col_sizes(int *col_sizes, t_list *lplist)
{
	t_lprint	*lp;
	char		*tmp;

	while (lplist)
	{
		lp = (t_lprint*)lplist->content;
		tmp = ft_strfill_right(lp->nlink, col_sizes[0], ' ');
		free(lp->nlink);
		lp->nlink = tmp;
		tmp = ft_strfill_right(lp->uid, col_sizes[1], ' ');
		free(lp->uid);
		lp->uid = tmp;
		tmp = ft_strfill_right(lp->gid, col_sizes[2], ' ');
		free(lp->gid);
		lp->gid = tmp;
		tmp = ft_strfill_right(lp->size, col_sizes[3], ' ');
		free(lp->size);
		lp->size = tmp;
		lplist = lplist->next;
	}
}

/*
** Actually do the printing of an 'l line'.
*/

static void	real_print_l_line(unsigned long *total,
		int *col_sizes, t_list *lprintlist)
{
	ft_miniprint("total %l0d%\n", total);
	apply_col_sizes(col_sizes, lprintlist);
	ft_lstiter(lprintlist, &lprint_print);
}

/*
** Prints a file's mode, links, user, group, size, ...
** then prints a newline.
**
** params :
** 1) fileinfo to print
** 2) short name format ? 1 = yes, 0 = no
**
** NOTE: This function do not print anything until pos is equal to 2 (last)
*/

void		print_l_line(t_fileinfo *fileinfo, int short_name, int pos)
{
	static int				*col_sizes;
	static unsigned	long	total = 0;
	static t_list			*lprintlist = NULL;
	static t_list			*lprintlist_tail = NULL;
	t_lprint				*lp_new;

	if (!col_sizes)
		col_sizes = ft_memalloc(4 * sizeof(int));
	total += fileinfo->blocks;
	lp_new = lprint_new(fileinfo, short_name);
	lprintlist_tail = ft_lstpushback(&lprintlist_tail,
			ft_lstnew((void*)lp_new, sizeof(t_lprint)));
	if (!lprintlist)
		lprintlist = lprintlist_tail;
	read_col_sizes(col_sizes, lp_new);
	free(lp_new);
	if (pos == 1 || pos == 2)
	{
		real_print_l_line(&total, col_sizes, lprintlist);
		ft_lstdel(&lprintlist, &lprint_delete);
		lprintlist_tail = NULL;
		free(col_sizes);
		col_sizes = NULL;
		total = 0;
	}
}
