/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:42:18 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/22 20:09:28 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_object	*ft_object_new(t_type type, t_object *o)
{
	t_object	*new;

	if ((new = malloc(sizeof * new)))
	{
		new->type = type;
		new->pos = o->pos;
		new->translate = o->translate;
		new->rotate = o->rotate;
		new->normal = o->normal;
		new->material = o->material;
		new->radius = o->radius;
		new->angle = o->angle;
		new->next = NULL;
	}
	else
		ft_error();
	return (new);
}

void		ft_object_push_back(t_object **lst, t_object *new)
{
	t_object	*p;

	if (!lst || !new)
		return ;
	else if (!*lst)
		*lst = new;
	else 
	{
		p = *lst;
		while (p->next)
			p = p->next;
		p->next = new;
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
