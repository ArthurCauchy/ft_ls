/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 16:33:52 by acauchy           #+#    #+#             */
/*   Updated: 2017/12/14 18:15:20 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Prints the usage.
*/

void	print_error(void)
{
	ft_putendl("error");
}

void	print_usage(void)
{
	ft_putendl("usage: ft_ls [-lRart] [file...]");
}

void	print_illegal_option(char c)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(c);
	ft_putchar('\n');
}

void	print_errlist(t_errlist *errlist)
{
	while (errlist)
	{
		ft_putstr(errlist->input);
		ft_putstr(": ");
		ft_putendl(errlist->errmsg);
		errlist = errlist->next;
	}
}
