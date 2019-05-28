/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:42:18 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/22 18:22:31 by ebatchas         ###   ########.fr       */
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
		new->name = o->name;
		new->translate = o->translate;
		new->rotate = o->rotate;
		new->scale = (t_vector){1.0f, 1.0f, 1.0f};
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

	id = 1;
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
	else if (type == DISK)
		ft_object_push_back(lst, ft_disk_new());
	else if (type == BOX)
		ft_object_push_back(lst, ft_box_new());
	else if (type == TORUS)
		ft_object_push_back(lst, ft_torus_new());
	else if (type == CUBE)
		ft_object_push_back(lst, ft_cube_new());
}

void		ft_object_remove(t_object **s, int id)
{
	t_object	*p;
	t_object	*q;

	if (!s || !*s)
		return ;
	p = *s;
	if (p && p->id == id)
	{
		*s = (*s)->next;
		free(p);
		return ;
	}
	q = (*s)->next;
	while (q && q->id != id)
	{
		p = q;
		q = q->next;
	}
	if (q && q->id == id)
	{
		p->next = q->next;
		free(q);
		return ;
	}
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
