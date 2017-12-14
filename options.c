/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 10:01:37 by acauchy           #+#    #+#             */
/*   Updated: 2017/12/14 16:48:41 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** WARNING: 'options' parameter MUST be initialized as a NTCTS of min size of 6
** Return: how many options were found in this param (0 to n)
*/

static void	read_option(char *str, char *options, char opt)
{
	int		i;
	int		j;

	i = 0;
	if (str[i] != '-')
		return (0);
	++i;
	while (str[i])
	{
		if (str[i] == 'l'
				|| str[i] == 'R'
				|| str[i] == 'a'
				|| str[i] == 'r'
				|| str[i] == 't')
			options[opt_count++] = str[i];
		else
		{
			print_illegal_option(str[i]);
			print_usage(str[i]);
			exit(EXIT_SUCCESS);
		}
		++i;
	}
}

/*
** WARNING: 'options' parameter MUST be initialized as a NTCTS of min size of 6
*/

void		read_params(int argc, char **argv, char *options, t_flist *flist)
{
	int	i;
	int	j;
	int	opt_count;
	int	stop;

	i = 0;
	j = 0;
	opt_count = 0;
	stop = 0;
	while (!stop && i < argc)
	{
		while (argv[i][j])
		{
			if ()
		}
	}
}
