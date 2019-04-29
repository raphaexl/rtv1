/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:42:18 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/29 18:14:43 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_object	*ft_object_new(t_type type, t_object *o)
{
	t_object	*new;

	if ((new = malloc(sizeof(*new))))
	{
		new->type = type;
		new->pos = o->pos;
		new->id = 0;
		new->name = ft_get_object_name(new);
		new->translate = o->translate;
		new->rotate = o->rotate;
		new->normal = o->normal;
		new->material = o->material;
		new->radius = o->radius;
		new->angle = o->angle;
		new->next = NULL;
	}
	else
		ft_print_error("malloc error");
	return (new);
}

void		ft_object_push_back(t_object **lst, t_object *new)
{
	t_object	*p;
	int			id;

	id = 0;
	if (!lst || !new)
		return ;
	else if (!*lst)
	{
		new->id = 0;
		*lst = new;
	}
	else
	{
		p = *lst;
		while (p->next && ++id)
			p = p->next;
		new->id = id;
		p->next = new;
	}
}

void		ft_object_add_back(t_object **lst, t_type type)
{
	if (type == SPHERE)
		ft_object_push_back(lst, ft_sphere_new());
	else if (type == PLANE)
		ft_object_push_back(lst, ft_plane_new());
	else if (type == CONE)
		ft_object_push_back(lst, ft_cone_new());
	else if (type == CYLINDRE)
		ft_object_push_back(lst, ft_cylindre_new());
}

char	*ft_get_object_name(t_object *o)
{
	if (o->type == SPHERE)
		return ("SPHERE");
	else if (o->type == CONE)
		return ("CONE");
	else if (o->type == CYLINDRE)
		return ("CYLINDRE");
	else if (o->type == PLANE)
		return ("PLANE");
	else
		return ("NONE");
}

void		ft_object_clean(t_object **lst)
{
	t_object	*p;

	if (!lst || !*lst)
		return ;
	p = *lst;
	while (p)
	{
		(*lst) = (*lst)->next;
		free(p);
		p = (*lst);
	}
}
