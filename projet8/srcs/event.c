/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:10:56 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/05 17:49:14 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		ft_env_update_camera(t_camera *cam, t_input *in)
{
	int		ret;

	ret = 0;
	if (in->keys[SDL_SCANCODE_W] && (ret = 1))
		cam->rot.x += 5.212;
	if (in->keys[SDL_SCANCODE_S] && (ret = 1))
		cam->rot.x -= 5.214;
	if (in->keys[SDL_SCANCODE_Q] && (ret = 1))
		cam->rot.z += 5.212;
	if (in->keys[SDL_SCANCODE_E] && (ret = 1))
		cam->rot.z -= 5.214;
	if (in->keys[SDL_SCANCODE_A] && (ret = 1))
		cam->trans.x -= 2.5;
	if (in->keys[SDL_SCANCODE_D] && (ret = 1))
		cam->trans.x += 2.5;
	if (in->keys[SDL_SCANCODE_LEFT] && (ret = 1))
		cam->rot.y -= 5.5;
	if (in->keys[SDL_SCANCODE_RIGHT] && (ret = 1))
		cam->rot.y += 5.5;
	if (in->keys[SDL_SCANCODE_UP] && (ret = 1))
		cam->trans.z += 2.5;
	if (in->keys[SDL_SCANCODE_DOWN] && (ret = 1))
		cam->trans.z -= 2.5;
	ft_camera_transform(cam);
	return (ret);
}

void	ft_env_select_object(t_env *e, int x, int y)
{
	t_intersect	inter;
	int			start_x;
	int			start_y;

	start_x = START_X;
	start_y = START_Y;
	e->selected = NULL;
	if (x < START_X || x > END_X)
		return ;
	if (y < START_Y || y > END_Y)
		return ;
	inter.ray = ft_camera_ray(&e->s.cam, x - start_x, W_H - (y - start_y));
	inter.t = INFINITY;
	if (ft_scene_intersect(&e->s, &inter))
		e->selected = inter.current;
}
