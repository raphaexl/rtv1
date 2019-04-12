/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 18:24:32 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/03 20:06:47 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_light		*ft_light_new(t_vector pos, t_color color)
{
	t_light	*new;

	if ((new = malloc(sizeof * new)))
	{
		new->pos = pos;
		new->intensity = color;
		new->next = NULL;
	}
	else
		ft_error();
	return (new);
}

void		ft_light_push_back(t_light **lst, t_light *new)
{
	t_light	*p;

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

void		ft_light_push_front(t_light **lst, t_light *new)
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

void		ft_light_pop_back(t_light **lst)
{
	t_light	*p;
	t_light	*q;

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

void		ft_light_clean(t_light **lst)
{
	t_light	*p;

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

int			ft_light_length(t_light *lst)
{
	if (!lst)
		return (0);
	else
		return (1 + ft_light_length(lst->next));
}
