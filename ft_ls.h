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
# include <sys/sysmacros.h>
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
void		print_errlist(t_errlist *errlist);

/*
** output_l.c
*/

void		print_l_line(t_filelist *filelist);

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

int			option_check(char *options, char opt_char);
int			read_option(char *str, char *options);

/*
** fileinfo.c
*/

t_fileinfo	*fileinfo_new(char *input, struct stat *file_info);

/*
** compare.c
*/

int					cmp_default(t_filelist* fl1, t_filelist *fl2);
int					cmp_r(t_filelist* fl1, t_filelist *fl2);
int					cmp_t(t_filelist* fl1, t_filelist *fl2);
int					cmp_tr(t_filelist* fl1, t_filelist *fl2);

/*
** filelist.c
*/

int			load_file(char *options, char *input, t_filelist **filelist);

/*
** errlist.c
*/

void		register_err(char *input, t_errlist **errlist);

#endif
