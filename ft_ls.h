/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 10:40:01 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/08 14:26:36 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#ifndef __APPLE__
# include <sys/sysmacros.h>
#endif

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
	quad_t	blocks;
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
** process_inputs.c
*/

void		process_inputs(t_filelist *filelist, t_dirlist *dirlist);
void		process_files(t_filelist *filelist, int short_name);

/*
** process_dirs.c
*/

void		process_dirs(t_dirlist *dirlist);

/*
** output.c
*/

void		print_error(char *errmsg);
void		print_file_error(char *filepath);
void		print_usage(void);
void		print_illegal_option(char c);
void		print_errlist(t_errlist *errlist);

/*
** output_dir.c
*/

void		print_dir(t_dirlist *dir, t_filelist *files, int total);

/*
** output_file.c
*/

void		print_file(t_fileinfo *fileinfo, int short_name, int pos);
void		print_default(t_fileinfo *fileinfo, int short_name, int pos);
void		print_line(t_fileinfo *fileinfo, int short_name);

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
void				fileinfo_delete(t_fileinfo *fileinfo);

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
void				filelist_delete(t_filelist *filelist);

/*
** dirlist.c
*/

t_dirlist 	*dirlist_new(char *input, struct stat *stat_info);
t_dirlist		**dirlist_add(t_dirlist **dirlist, t_dirlist *new);
void				dirlist_delete(t_dirlist *dirlist);

/*
** errlist.c
*/

void		register_err(char *input, t_errlist **errlist);

#endif
