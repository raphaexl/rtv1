/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:53:37 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/05 20:57:48 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <time.h>
# include "SDL2/SDL_image.h"
# include "SDL2/SDL_ttf.h"
# include "SDL2/SDL_thread.h"
# include "raytrace.h"

typedef struct		s_input
{
	int		quit;
	int		mousex;
	int		mousey;
	int		mouse[6];
	int		keys[SDL_NUM_SCANCODES];
}					t_input;

typedef struct		s_menu
{
	SDL_Rect		pos[NB_OPTIONS];
	SDL_Texture		*img[NB_OPTIONS];
	int				keys[NB_OPTIONS];
}					t_menu;

typedef	struct		s_ptr
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
}					t_ptr;

typedef	struct		s_env
{
	t_scene			s;
	t_menu			menu;
	t_ptr			ptr;
	Uint32			*pixels;
	int				optimize;
	int				delta;
	t_object		*selected;
}					t_env;
#endif
