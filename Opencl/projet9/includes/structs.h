/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:53:37 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/10 20:31:10 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <time.h>
# include <assert.h>
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

typedef struct		s_opencl
{
	cl_platform_id		platform_id;
	cl_device_id		device_id;
	cl_uint				ret_num_platforms;
	cl_uint				ret_num_devices;
	cl_int				ret;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_mem				scene_mem_obj;
	cl_mem				pixels_mem_obj;
	cl_program			program;
	cl_kernel			kernel;
	size_t				global_iterm_size;
	size_t				local_iterm_size;
}					t_opencl;

typedef	struct		s_env
{
	int				optimize;
	int				start;
	Uint32			*pixels;
	t_object		*selected;
	t_scene			s;
	t_menu			menu;
	t_ptr			ptr;
}					t_env;
#endif