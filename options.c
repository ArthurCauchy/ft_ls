/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 10:01:37 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/18 10:36:39 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Check if the option is set.
** return 1 : yes, return 0 : no
*/

int			option_check(char opt_char)
{
	int	i;

	i = 0;
	while (g_options[i])
	{
		if (g_options[i] == opt_char)
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

static void	add_option(char opt_char)
{
	static int	opt_count = 0;

	if (!option_check(opt_char))
		g_options[opt_count++] = opt_char;
}

static int	is_valid_option(char opt_char)
{
	if (opt_char == 'l'
			|| opt_char == 'R'
			|| opt_char == 'a'
			|| opt_char == 'r'
			|| opt_char == 't'
			|| opt_char == 'S'
			|| opt_char == 'd'
			|| opt_char == '1')
		return (1);
	return (0);
}

/*
** WARNING: 'options' parameter MUST be initialized
** as a NTCTS of min size of 6 (\0 included)
** Return: 0 if str isn't an option, 1 if it is, 2 if it's '--'
*/

int			read_option(char *str)
{
	int		i;

	i = 0;
	if (str[i] != '-')
		return (0);
	++i;
	if (str[i] == '-')
		return (2);
	while (str[i])
	{
		if (is_valid_option(str[i]))
			add_option(str[i]);
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
