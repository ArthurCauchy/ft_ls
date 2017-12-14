/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 10:01:37 by acauchy           #+#    #+#             */
/*   Updated: 2017/12/14 19:00:13 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** WARNING: 'options' parameter MUST be initialized
** as a NTCTS of min size of 6 (\0 included)
** Check if the option is already in the option array,
** and if it isn't, add it.
*/

static void	add_option(char *options, char opt_char)
{
	static int	opt_count = 0;
	int			i;

	i = 0;
	while (options[i])
	{
		if (options[i] == opt_char)
			return ;
		++i;
	}
	options[opt_count++] = opt_char;
}

/*
** WARNING: 'options' parameter MUST be initialized
** as a NTCTS of min size of 6 (\0 included)
** Return: 0 if str isn't an option, 1 if it is
*/

static int	read_option(char *str, char *options)
{
	int		i;

	i = 0;
	if (str[i] != '-')
		return (0);
	++i;
	/*if (str[i] == '-')
		return (-1); IS IT REALLY USEFULL ? */
	while (str[i])
	{
		if (str[i] == 'l'
				|| str[i] == 'R'
				|| str[i] == 'a'
				|| str[i] == 'r'
				|| str[i] == 't')
			add_option(options, str[i]);
		else
		{
			print_illegal_option(str[i]);
			print_usage();
			exit(EXIT_FAILURE);
		}
		++i;
	}
	return (1);
}

/*
** WARNING: 'options' parameter MUST be initialized
** as a NTCTS of min size of 6 (\0 included)
*/

void		read_params(int argc, char **argv, char *options/*, t_flist *flist*/)
{
	int	i;
	int	is_opt;

	i = 1;
	is_opt = 1;
	while (i < argc)
	{
		if (is_opt && !read_option(argv[i], options))
		{
			is_opt = 0;
		}
		if (!is_opt)
		{
			// add it to file list flist
		}
		++i;
	}
}
