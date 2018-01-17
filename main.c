/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 10:36:33 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/17 13:33:53 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		g_retcode = EXIT_SUCCESS;
char	g_options[64];

int		main(int argc, char **argv)
{
	t_filelist	*filelist;
	t_dirlist	*dirlist;
	t_errlist	*errlist;

	argc = argc * 0;
	filelist = NULL;
	dirlist = NULL;
	errlist = NULL;
	read_params(argv, &filelist, &dirlist, &errlist);
	if (errlist)
		g_retcode = EXIT_FAILURE;
	print_errlist(errlist);
	process_inputs(filelist, dirlist, errlist);
	return (g_retcode);
}
