/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 17:35:57 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/10 19:36:07 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <assert.h>
# include "libft.h"
# include "complex.h"
# include "vector.h"
# include "raytrace.h"


typedef struct		s_point
{
	int		x;
	int		y;
}					t_point;

typedef	struct		s_vect2d
{
	double	x;
	double	y;
}					t_vect2d;

typedef struct		s_input
{
	int		quit;
	int		mousex;
	int		mousey;
	int		xwheel;
	int		ywheel;
	int		mousexrel;
	int		mouseyrel;
	int		mouse[6];
	int		keys[SDL_NUM_SCANCODES];
}					t_input;

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
	cl_uint				w;
	cl_uint				h;
	cl_context			context;
	cl_command_queue	command_queue;
	t_scene				scene;
	cl_mem				scene_mem_obj;
	cl_mem				pixels_mem_obj;
	cl_program			program;
	cl_kernel			kernel;
	size_t				global_iterm_size;
	size_t				local_iterm_size;
}					t_opencl;

int			ft_color1( int i, int imax);
int			ft_rgb_color(unsigned int r, unsigned int g, unsigned int b);
t_point		ft_point(int x, int y);
int			ft_color2(int	k, int n);

double		ft_homothetie(double start, double end, double rapport);

void		ft_sdl_draw_octant1(Uint32 *pixels, t_point p1, t_point p2, Uint32 color);
void		ft_sdl_draw_octant2(Uint32 *pixels, t_point p1, t_point p2, Uint32 color);
void		ft_sdl_draw_line(Uint32 *pixels, t_point p1, t_point p2, Uint32 color);
void		ft_sdl_draw_circle(Uint32 *pixels, t_point co, int radius , Uint32 color);
void		ft_sdl_draw_disc(Uint32 *pixels, t_point co, int radius, Uint32 color);

void		ft_draw(t_scene *s, Uint32 *pixels);

void		ft_update_event(t_input *in);
int			ft_sdl_init(t_ptr *ptr, int width, int height, const char *title);
int			ft_update_renderer(t_ptr ptr, Uint32 *pixel, int width);
void		ft_sdl_error(void);
void		ft_sdl_put_pixel(Uint32 *pixels, int x, int y, int color);
void		ft_clear_pixels(Uint32 *pixels, t_point p);

void		ft_sdl_quit(t_ptr *ptr);
void		ft_error(void);


cl_platform_id	ft_cl_platform(void);
cl_device_id	ft_cl_device(cl_platform_id plateform_id);
cl_context		ft_cl_context(cl_device_id *device_id);
cl_command_queue ft_cl_command_queue(cl_context context, cl_device_id device_id);
cl_program		ft_cl_program(cl_context c, char *file_name);
void			ft_opencl_init(t_opencl *opencl, char *kernel_file);
void			ft_opencl_mem(t_opencl *opencl);
void			ft_opencl_kernel(t_opencl *opencl);
void			ft_opencl_quit(t_opencl *opencl);

#endif
