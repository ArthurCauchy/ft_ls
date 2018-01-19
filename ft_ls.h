/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 10:40:01 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/18 19:57:37 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# ifndef __APPLE__
#  include <sys/sysmacros.h>
# endif

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

/*
** Contains the code our program will returns at the end.
** Changed to EXIT_FAILURE if we encounter one or more error.
*/
extern int			g_retcode;

/*
** Contains the options given to the program.
** 1 char = 1 option
*/
extern char			g_options[64];

/*
** This struct can contain every useful info on a file.
*/
typedef struct	s_fileinfo
{
	char		*path;
	char		*mode;
	nlink_t		nlink;
	uid_t		uid;
	gid_t		gid;
	off_t		size;
	unsigned	blocks;
	time_t		mtime;
	char		*target_path;
	dev_t		major;
	dev_t		minor;
}				t_fileinfo;

/*
** Represents a list of files.
*/
typedef struct	s_filelist
{
	struct s_fileinfo	*fileinfo;
	struct s_filelist	*next;
}				t_filelist;

/*
** Represents a list of directories.
*/
typedef struct	s_dirlist
{
	struct s_fileinfo	*fileinfo;
	struct s_filelist	*files;
	struct s_dirlist	*next;
}				t_dirlist;

/*
** Represents a list of errors.
*/
typedef struct	s_errlist
{
	char				*input;
	char				*errmsg;
	struct s_errlist	*next;
}				t_errlist;

/*
** Represents a line of detailed print.
** Used to adjust col offsets before actually printing it.
*/
typedef struct	s_lprint
{
	char			*mode;
	char			*nlink;
	char			*uid;
	char			*gid;
	char			*size;
	char			*date;
	char			*filename;
}				t_lprint;

/*
** process_inputs.c
*/

void			process_inputs(t_filelist *filelist,
		t_dirlist *dirlist, t_errlist *errlist);
void			process_files(t_filelist *filelist, int short_name);

/*
** process_dirs.c
*/

void			process_dirs(t_dirlist *dirlist,
		t_filelist *filelist, t_errlist *errlist);

/*
** output.c
*/

void			print_error(char *errmsg);
void			print_file_error(char *filepath);
void			print_usage(void);
void			print_illegal_option(char c);
void			print_errlist(t_errlist *errlist);

/*
** output_dir.c
*/

void			print_dir(t_dirlist *dir, t_filelist *files, int is_first);

/*
** output_file.c
*/

void			print_file(t_fileinfo *fileinfo, int short_name, int pos);
void			print_default(t_fileinfo *fileinfo, int short_name, int pos);
void			print_line(t_fileinfo *fileinfo, int short_name);

/*
** output_l.c
*/

void			print_l_line(t_fileinfo *fileinfo, int short_name, int pos);

/*
** lprint.c
*/

void			lprint_delete(void *lprint, size_t size);
t_lprint		*lprint_new(t_fileinfo *fileinfo, int short_name);
void			lprint_print(t_list *elem);

/*
** utils.c
*/

void			exit_error(char *msg);
char			*get_name_only(char *path);
char			*get_filepath(char *dirpath, char *filename);
char			*time_to_str(time_t time);

/*
** params.c
*/

int				load_file(char *input, t_filelist **filelist,
		t_dirlist **dirlist);
void			read_params(char **argv, t_filelist **filelist,
		t_dirlist **dirlist, t_errlist **errlist);

/*
** options.c
*/

int				option_check(char opt_char);
int				read_option(char *str);

/*
** fileinfo.c
*/

char			*mode_to_str(mode_t file_mode);
char			*symlink_target_path(char *link_path, off_t file_size);
void			fileinfo_delete(t_fileinfo *fileinfo);

/*
** fileinfo2_default.c || fileinfo2_macos.c
*/

t_fileinfo		*fileinfo_new(char *input, struct stat *file_info);

/*
** compare.c
*/

int				cmp_default(t_fileinfo *f1, t_fileinfo *f2);
int				cmp_r(t_fileinfo *f1, t_fileinfo *f2);
int				cmp_t(t_fileinfo *f1, t_fileinfo *f2);
int				cmp_tr(t_fileinfo *f1, t_fileinfo *f2);

/*
** compare2.c
*/

int				cmp_s(t_fileinfo *f1, t_fileinfo *f2);
int				cmp_sr(t_fileinfo *f1, t_fileinfo *f2);

/*
** filelist.c
*/

t_filelist		*filelist_new(char *input, struct stat *stat_info);
t_filelist		**filelist_add(t_filelist **filelist, t_filelist *new);
void			filelist_delete(t_filelist *filelist);

/*
** dirlist.c
*/

t_dirlist		*dirlist_new(char *input, struct stat *stat_info);
t_dirlist		**dirlist_add(t_dirlist **dirlist, t_dirlist *new);
void			dirlist_delete(t_dirlist *dirlist);

/*
** errlist.c
*/

void			register_err(char *input, t_errlist **errlist);
void			delete_errlist(t_errlist *errlist);

#endif
