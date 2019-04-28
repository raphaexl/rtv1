/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:10:56 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/27 19:01:34 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		ft_debug(void)
{
	write(1, "debug!\n", 7);
	exit(0);
}

int	ft_env_update_camera(t_camera *cam, t_input *in)
{
	int		ret;

	ret = 0;
	if (in->keys[SDL_SCANCODE_W] && (ret = 1))
		cam->trans.y += 0.5;
	if (in->keys[SDL_SCANCODE_S] && (ret = 1))
		cam->trans.y -= 0.5;
	if (in->keys[SDL_SCANCODE_A] && (ret = 1))
		cam->trans.x -= 0.5;
	if (in->keys[SDL_SCANCODE_D] && (ret = 1))
		cam->trans.x += 0.5;
	if (in->keys[SDL_SCANCODE_KP_MINUS] && (ret = 1))
		cam->trans.z -= 0.5;
	if (in->keys[SDL_SCANCODE_KP_PLUS] && (ret = 1))
		cam->trans.z += 0.5;
	if (in->keys[SDL_SCANCODE_LEFT] && (ret = 1))
		cam->rot.y += 5.5;
	if (in->keys[SDL_SCANCODE_RIGHT] && (ret = 1))
		cam->rot.y -= 5.5;
	if (in->keys[SDL_SCANCODE_UP] && (ret = 1))
		cam->rot.x += 5.212;
	if (in->keys[SDL_SCANCODE_DOWN] && (ret = 1))
		cam->rot.x -= 5.214;
	if (in->wheel && (ret = 1))
	{
		cam->fov = (cam->fov + in->wheel * DELTA_ANGLE);
		write(1, "Hi\n", 3);
	}
	cam->fov = ft_clamp(0.0, 179.0, cam->fov);
	cam->h = tan((cam->fov * M_PI * (1.0 / 180.0)) / 2.0);
	cam->w = cam->ratio * cam->h;
	ft_camera_transform(cam);
	return (ret);
}


void	ft_env_select_object(t_env *e, int x, int y)
{
	t_object	*p;
	t_object	**q;
	t_intersect	inter;

	p = NULL;
	e->selected = NULL;
	if (x < START_X || x > END_X)
		return ;
	if (y < START_Y || y > END_Y)
		return ;
	inter.ray = ft_camera_ray(&e->s.cam, x - START_X, y - START_Y);
	inter.t = INFINITY;
	if (ft_scene_intersect(&e->s, &inter))
		p = inter.current;
	if (p)
	{
		p = e->s.obj;
		while (p && p->id != inter.current->id)
			p = p->next;
		if (p  && (q = &p))
			e->selected = p;
	}
}
