/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 10:01:37 by acauchy           #+#    #+#             */
/*   Updated: 2017/12/18 13:23:26 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Check if the option is set.
** return 1 : yes, return 0 : no
*/

int		option_check(char *options, char opt_char)
{
	int	i;

	i = 0;
	while (options[i])
	{
		if (options[i] == opt_char)
			return (1);
		++i;
	}
	return (0);
}

/*
** WARNING: 'options' parameter MUST be initialized
** as a NTCTS of min size of 6 (\0 included)
** Check if the option is already in the option array,
** and if it isn't, add it.
*/

static void	add_option(char *options, char opt_char)
{
	static int	opt_count = 0;

	if (!option_check(options, opt_char))
		options[opt_count++] = opt_char;
}

/*
** WARNING: 'options' parameter MUST be initialized
** as a NTCTS of min size of 6 (\0 included)
** Return: 0 if str isn't an option, 1 if it is
*/

int		read_option(char *str, char *options)
{
	int		i;

	i = 0;
	if (str[i] != '-')
		return (0);
	++i;
	if (str[i] == '-')
		return (0);
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
