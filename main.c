/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 10:36:33 by acauchy           #+#    #+#             */
/*   Updated: 2017/12/18 16:27:20 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int argc, char **argv)
{
	char		*options;
	t_filelist	*filelist;
	t_errlist	*errlist;

	argc = argc * 0;
	filelist = NULL;
	errlist = NULL;
	if (!(options = ft_strnew(5)))
		exit_error();
	read_params(argv, options, &filelist, &errlist);
	ft_putendl(options);
	print_errlist(errlist);
	t_filelist *cur = filelist;
	while (cur)
	{
		print_l_line(cur);
		cur = cur->next;
	}
	// et ensuite il faut tout free
	return (EXIT_SUCCESS);
}
