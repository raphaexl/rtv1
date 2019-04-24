/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:53:37 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/24 15:52:45 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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
	SDL_Texture		*img[NB_OPTIONS];
	SDL_Rect		pos[NB_OPTIONS];
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
	int				optimize;
	t_ptr			ptr;
	t_menu			menu;
	t_scene			s;
	Uint32			*pixels;
}					t_env;
typedef struct		s_arg
{
	t_env			e;
	int				k;
	int				start;
}					t_arg;

#endif
