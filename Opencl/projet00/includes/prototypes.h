/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 15:51:10 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/07 13:33:19 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <assert.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>
# define SCR_WIDTH 1280
# define SCR_HEIGHT 720
# define W_W 1280
# define W_H 720
# define ERR_CHECK(cond) if (!(cond)) perror(SDL_GetError());
# ifdef __APPLE__
# include<OpenCL/opencl.h>
# else
# include <CL/cl.h>
#endif

# define MAX_SOURCE_SIZE (0x1000000)
# define LIST_SIZE 1024

typedef struct		s_input
{
	int		quit;
	int		mousex;
	int		mousey;
	int		mouse[6];
	int		keys[SDL_NUM_SCANCODES];
}					t_input;

typedef	struct			s_ptr
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Texture			*texture;
}						t_ptr;

typedef struct			s_opencl
{
	cl_platform_id		platform_id;
	cl_device_id		device_id;
	cl_uint				ret_num_platforms;
	cl_uint				ret_num_devices;
	cl_int				ret;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_mem				cpu_mem_obj;
	cl_program			program;
	cl_kernel			kernel;
	size_t				global_iterm_size;
	size_t				local_iterm_size;
}						t_opencl;

cl_platform_id			ft_cl_platform(void);
cl_device_id			ft_cl_device(cl_platform_id plateform_id);
cl_context				ft_cl_context(cl_device_id *device_id);
cl_command_queue		ft_cl_command_queue(cl_context context, cl_device_id device_id);
cl_program				ft_cl_program(cl_context c, char *file_name);
void					ft_opencl_init(t_opencl *opencl, char *kernel_file);
void					ft_opencl_mem(t_opencl *opencl);
void					ft_opencl_kernel(t_opencl *opencl);
void					ft_opencl_quit(t_opencl *opencl);

int						ft_sdl_init(t_ptr *ptr, const char *title);
void					ft_update_event(t_input *in);
void					ft_clear_pixels(Uint32 *pixels);
int						ft_update_renderer(t_ptr *ptr, Uint32 *pixels);
void					ft_sdl_quit(t_ptr *ptr);

#endif
