/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 10:40:01 by acauchy           #+#    #+#             */
/*   Updated: 2017/12/18 16:32:50 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <errno.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "libft.h"

typedef struct	s_fileinfo
{
	char	*path;
	char	*mode;
	nlink_t	nlink;
	uid_t	uid;
	gid_t	gid;
	off_t	size;
	time_t	mtime;
	char	*target_path;
	dev_t	major;
	dev_t	minor;
}				t_fileinfo;

typedef struct	s_filelist
{
	struct s_fileinfo	*fileinfo;
	struct s_filelist	*next;
}				t_filelist;

typedef struct	s_errlist
{
	char				*input;
	char				*errmsg;
	struct s_errlist	*next;
}				t_errlist;

/*
** output.c
*/

void		print_error(void);
void		print_usage(void);
void		print_illegal_option(char c);

/*
** utils.c
*/

void		exit_error(void);

/*
** params.c
*/

void		read_params(char **argv, char *options, t_filelist **filelist, t_errlist **errlist);

/*
** options.c
*/

int			read_option(char *str, char *options);

/*
** fileinfo.c
*/

t_fileinfo	*fileinfo_new(char *input, struct stat *file_info);

/*
** filelist.c
*/

int			load_file(char *options, char *input, t_filelist **filelist);

#endif
