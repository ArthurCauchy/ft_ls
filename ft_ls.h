/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 10:40:01 by acauchy           #+#    #+#             */
/*   Updated: 2017/12/21 17:03:21 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/stat.h>
# include <sys/types.h>
# include <sys/sysmacros.h> // file not found on DARWIN
# include <pwd.h>
# include <grp.h>
# include <errno.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <dirent.h>
# include "libft.h"

# define MAX_PATH_SIZE 4096

extern char			g_options[64];;

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
}								t_filelist;

typedef struct	s_dirlist
{
	struct s_fileinfo	*fileinfo;
	struct s_filelist	*files;
	struct s_dirlist	*next;
}								t_dirlist;

typedef struct	s_errlist
{
	char				*input;
	char				*errmsg;
	struct s_errlist	*next;
}								t_errlist;

/*
** output.c
*/

void		print_error(void);
void		print_usage(void);
void		print_illegal_option(char c);
void		print_errlist(t_errlist *errlist);

/*
** output_dir.c
*/

void		print_dir(t_dirlist *dir);

/*
** output_l.c
*/

void		print_l_line(t_fileinfo *fileinfo, int short_name);

/*
** utils.c
*/

void		exit_error(void);
char		*get_name_only(char *path);
char		*get_filepath(char *dirpath, char *filename);

/*
** params.c
*/

int			load_file(char *input, t_filelist **filelist, t_dirlist **dirlist);
void		read_params(char **argv, t_filelist **filelist, t_dirlist **dirlist, t_errlist **errlist);

/*
** options.c
*/

int			option_check(char opt_char);
int			read_option(char *str);

/*
** fileinfo.c
*/

t_fileinfo	*fileinfo_new(char *input, struct stat *file_info);

/*
** compare.c
*/

int					cmp_default(t_fileinfo *f1, t_fileinfo *f2);
int					cmp_r(t_fileinfo *f1, t_fileinfo *f2);
int					cmp_t(t_fileinfo *f1, t_fileinfo *f2);
int					cmp_tr(t_fileinfo *f1, t_fileinfo *f2);

/*
** filelist.c
*/

t_filelist  *filelist_new(char *input, struct stat *stat_info);
t_filelist  **filelist_add(t_filelist **filelist, t_filelist *new);

/*
** dirlist.c
*/

t_dirlist 	*dirlist_new(char *input, struct stat *stat_info);
t_dirlist		**dirlist_add(t_dirlist **dirlist, t_dirlist *new);

/*
** errlist.c
*/

void		register_err(char *input, t_errlist **errlist);

#endif
