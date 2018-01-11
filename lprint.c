/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lprint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 10:55:47 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/11 18:33:18 by arthur           ###   ########.fr       */
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

t_lprint	*lprint_new(t_fileinfo *fileinfo, int short_name)
{
	t_lprint	*new;
	char		*major;
	char		*tmp;
	char		*minor;
	
	new = (t_lprint*)malloc(sizeof(t_lprint));
	new->mode = ft_strdup(fileinfo->mode);
	new->nlink = ft_itoa(fileinfo->nlink);
	new->uid = (getpwuid(fileinfo->uid)) ?
		ft_strdup(getpwuid(fileinfo->uid)->pw_name) : ft_itoa(fileinfo->uid);
	new->gid = (getgrgid(fileinfo->gid)) ?
		ft_strdup(getgrgid(fileinfo->gid)->gr_name) : ft_itoa(fileinfo->gid);
	if (fileinfo->mode[0] == 'b' || fileinfo->mode[0] == 'c')
	{
		tmp = ft_itoa(fileinfo->major);
		major = ft_strfill_right(tmp, 3, ' ');
		free(tmp);
		tmp = ft_itoa(fileinfo->minor);
		minor = ft_strfill_right(tmp, 3, ' ');
		free(tmp);
		new->size = ft_strjoin_free(major,
				ft_strjoin_free(ft_strdup(", "), minor));
	}
	else
		new->size = ft_lltoa(fileinfo->size);
	new->date = time_to_str(fileinfo->mtime);
	new->filename = short_name ? ft_strdup(get_name_only(fileinfo->path)) : ft_strdup(fileinfo->path);
	return (new);
}

void		lprint_print(t_list *elem)
{
	ft_putstr(((t_lprint*)elem->content)->mode);
	ft_putstr(((t_lprint*)elem->content)->nlink);
	ft_putstr(((t_lprint*)elem->content)->uid);
	ft_putstr(((t_lprint*)elem->content)->gid);
	ft_putstr(((t_lprint*)elem->content)->size);
	ft_putstr(((t_lprint*)elem->content)->date);
	ft_putstr(((t_lprint*)elem->content)->filename);
	ft_putchar('\n');
}
