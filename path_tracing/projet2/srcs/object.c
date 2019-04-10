/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:42:18 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/08 15:41:54 by ebatchas         ###   ########.fr       */
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
		new->id = 0;
		new->name =  ft_get_object_name(new);
		printf("Position : %.2lf\t %.2lf\t %.2lf\n", o->pos.x, o->pos.y, o->pos.z);
		printf("Translate : %.2lf\t %.2lf\t %.2lf\n", o->translate.x, o->translate.y, o->translate.z);
		printf("Rotate : %.2lf\t %.2lf\t %.2lf\n", o->rotate.x, o->rotate.y, o->rotate.z);
		printf("Normal : %.2lf\t %.2lf\t %.2lf\n", o->normal.x, o->normal.y, o->normal.z);
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

void		ft_object_push_front(t_object **lst, t_object *new)
{
	if (!lst || !new)
		return ;
	else if (!*lst)
		*lst = new;
	else
	{
		new->next = *lst;
		*lst = new;
	}
}

void		ft_object_pop_back(t_object **lst)
{
	t_object	*p;
	t_object	*q;

	if (!lst || !*lst)
		return ;
	else if (!(*lst)->next)
	{
		free(*lst);
		lst = NULL;
	}
	else
	{
		p = (*lst)->next;
		while (p)
		{
			q = p;
			p = p->next;
		}
		free(p);
		q->next = NULL;
	}
}

t_object	*ft_object_get(t_object	*lst, int	id)
{
	t_object	*p;

	if (!lst)
		return (NULL);
	p = lst;
	while (p && p->id != id)
		p = p->next;
	return (p);
}

void		ft_object_set_id(t_object **lst)
{
	t_object	*p;
	int			i;

	p = *lst;
	i = -1;
	while (p)
	{
		p->id = (++i);
		p = p->next;
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

int			ft_object_length(t_object *lst)
{
	if (!lst)
		return (0);
	else
		return (1 + ft_object_length(lst->next));
}
