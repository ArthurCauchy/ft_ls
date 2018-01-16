/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lprint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 10:55:47 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/16 21:09:32 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		lprint_delete(void *lprint, size_t size)
{
	size = 0 * size;

	free(((t_lprint*)lprint)->mode);
	free(((t_lprint*)lprint)->nlink);
	free(((t_lprint*)lprint)->uid);
	free(((t_lprint*)lprint)->gid);
	free(((t_lprint*)lprint)->size);
	free(((t_lprint*)lprint)->date);
	free(((t_lprint*)lprint)->filename);
	free(lprint);
}

static char	*major_minor_to_str(t_fileinfo *fileinfo)
{
	char	*maj;
	char	*min;
	char	*tmp;
	char	*final;

	tmp = ft_itoa(fileinfo->major);
	maj = ft_strfill_right(tmp, 3, ' ');
	free(tmp);
	tmp = ft_itoa(fileinfo->minor);
	min = ft_strfill_right(tmp, 3, ' ');
	free(tmp);
	final = ft_strjoin_free(maj, ft_strjoin_free(ft_strdup(", "), min));
	return (final);
}

static char *name_and_syml_to_str(t_fileinfo *fileinfo, int short_name)
{
	char	*final;

	if (short_name)
		final = ft_strdup(get_name_only(fileinfo->path));
	else
		final = ft_strdup(fileinfo->path);
	if (fileinfo->target_path)
	{
		final = ft_strjoin_free(final, ft_strdup(" -> "));
		final = ft_strjoin_free(final, ft_strdup(fileinfo->target_path));
	}
	return (final);
}

t_lprint	*lprint_new(t_fileinfo *fileinfo, int short_name)
{
	t_lprint	*new;
	
	new = (t_lprint*)malloc(sizeof(t_lprint));
	new->mode = ft_strdup(fileinfo->mode);
	new->nlink = ft_itoa(fileinfo->nlink);
	new->uid = (getpwuid(fileinfo->uid)) ?
		ft_strdup(getpwuid(fileinfo->uid)->pw_name) : ft_itoa(fileinfo->uid);
	new->gid = (getgrgid(fileinfo->gid)) ?
		ft_strdup(getgrgid(fileinfo->gid)->gr_name) : ft_itoa(fileinfo->gid);
	if (fileinfo->mode[0] == 'b' || fileinfo->mode[0] == 'c')
		new->size = major_minor_to_str(fileinfo);
	else
		new->size = ft_lltoa(fileinfo->size);
	new->date = time_to_str(fileinfo->mtime);
	new->filename = name_and_syml_to_str(fileinfo, short_name);
	return (new);
}

void		lprint_print(t_list *elem)
{
	ft_putstr(((t_lprint*)elem->content)->mode);
	ft_putchar(' ');
	ft_putstr(((t_lprint*)elem->content)->nlink);
	ft_putchar(' ');
	ft_putstr(((t_lprint*)elem->content)->uid);
	ft_putchar(' ');
	ft_putstr(((t_lprint*)elem->content)->gid);
	ft_putchar(' ');
	ft_putstr(((t_lprint*)elem->content)->size);
	ft_putchar(' ');
	ft_putstr(((t_lprint*)elem->content)->date);
	ft_putchar(' ');
	ft_putstr(((t_lprint*)elem->content)->filename);
	ft_putchar('\n');
}
