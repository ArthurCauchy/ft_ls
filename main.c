/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 10:36:33 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/18 18:57:14 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Contains the code our program will returns at the end.
** Changed to EXIT_FAILURE if we encounter one or more error.
*/
int		g_retcode = EXIT_SUCCESS;

/*
** Contains the options given to the program.
** 1 char = 1 option
*/
char	g_options[64];

/*
** The main function. Starts everything we need.
*/

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
	delete_errlist(errlist);
	process_inputs(filelist, dirlist, errlist);
	return (g_retcode);
}
