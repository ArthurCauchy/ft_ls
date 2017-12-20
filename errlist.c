#include "ft_ls.h"

static t_errlist	*errlist_new(char *input, char *errmsg)
{
	t_errlist	*new;

	if (!(new = (t_errlist*)malloc(sizeof(t_errlist))))
		return (NULL);
	new->input = input;
	new->errmsg = errmsg;
	new->next = NULL;
	return (new);
}

static t_errlist	**errlist_add(t_errlist **errlist, t_errlist *new)
{
	t_errlist	*cur;

	if (!*errlist)
		*errlist = new;
	else
	{
		cur = *errlist;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
	return (errlist);
}

void							register_err(char *input, t_errlist **errlist)
{
	char			*errmsg;
	t_errlist *new;

	errmsg = ft_strdup(strerror(errno));
	if (!errmsg || !(new = errlist_new(input, errmsg)))
		exit_error();
	errlist_add(errlist, new);
}
