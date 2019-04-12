/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 20:04:01 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/08 16:12:34 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define SCR_WIDTH 1200
# define SCR_HEIGHT 1024
# define W_W 800
# define W_H 400
# define B_W 800
# define B_H 400
# define START_X (SCR_WIDTH - W_W) / 2
# define START_Y (SCR_HEIGHT - W_H) / 2
# define END_X W_W + START_X
# define END_Y  W_H + START_Y
# define NB_THREADS 200
# define NB_OPTIONS 18
# define DELTA_ANGLE 10
# define ERR_CHECK(cond) if (!(cond)) perror(SDL_GetError());

# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>
# include <sys/stat.h>
# include <math.h>
# include <fcntl.h>
# include "libft.h"
# include "matrix.h"
# include "raytrace.h"
# include <pthread.h>

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

typedef struct 		s_menu
{
	SDL_Texture		*img[NB_OPTIONS];
	SDL_Rect		pos[NB_OPTIONS];
	int				keys[NB_OPTIONS];
	t_options		option[ROTATE_Z + 1];
}					t_menu;

typedef	struct		s_ptr
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
}					t_ptr;

typedef	struct		s_env
{
	t_ptr		ptr;
	t_menu		menu;
	t_scene		s;
	t_object	*selected;
	Uint32		*pixels;
}					t_env;

int			ft_rgb_color(unsigned int r, unsigned int g, unsigned int b);
float		ft_rand48(void);
void		ft_error(void);
void		ft_print_error(char *str);
t_point		ft_point(int x, int y);
t_vect2d	ft_vect2d(float x, float y);
t_font		ft_font(const char *message, const char *font_file, int font_size);
char		*ft_get_object_name(t_object *p);

	
void		ft_draw(t_scene *s, Uint32 *pixels, t_menu *m);

void		ft_sdl_draw_octant1(Uint32 *pixels, t_point p1, t_point p2, Uint32 color);
void		ft_sdl_draw_octant2(Uint32 *pixels, t_point p1, t_point p2, Uint32 color);
void		ft_sdl_draw_line(Uint32 *pixels, t_point p1, t_point p2, Uint32 color);
void		ft_sdl_draw_circle(Uint32 *pixels, t_point co, int radius , Uint32 color);
void		ft_sdl_draw_disc(Uint32 *pixels, t_point co, int radius, Uint32 color);

void		ft_update_event(t_input *in);
int			ft_sdl_init(t_ptr *ptr, int width, int height, const char *title);
int			ft_update_renderer(t_ptr *ptr, Uint32 *pixel);
SDL_Texture	*ft_get_render_text(SDL_Renderer *rend, t_font f, SDL_Color color);
void		ft_render_draw_img(SDL_Renderer *r, SDL_Texture *i, t_point p,\
		SDL_Rect *pos);
void		ft_sdl_error(void);
void		ft_sdl_put_pixel(Uint32 *pixels, int x, int y, int color);
void		ft_clear_pixels(Uint32 *pixels);

void		ft_sdl_quit(t_ptr *ptr);
int			ft_env_load_all(t_env *e);
int			ft_env_load_images(t_env *env);
int			ft_env_init(t_env *e, char *file);
void		ft_env_update_camera(t_env *e, t_input *in);
void		ft_env_select_object(t_env *e, int mousex, int mousey);
void		ft_process_event(t_env *e, t_input *in);
void		ft_update_options(t_menu *m, t_input *in, int k);
int			ft_mouse_inside(int mousex, int mousey, SDL_Rect *r);
int			ft_env_draw(t_env *e);
void		ft_env_quit(t_env *e);

t_vector	ft_rotate_x(t_vector r, float angle);
t_vector	ft_rotate_y(t_vector r, float angle);
t_vector	ft_rotate_z(t_vector r, float angle);
t_vector	ft_rotate_vec3(t_vector r, t_vector v, int invert);
t_vector	ft_translate_vec3(t_vector r, t_vector v, int invert);
t_color		ft_background_color(t_ray *r);
t_color		ft_get_light(t_intersect *in, t_light *light);
t_color		ft_trace(t_color c, t_intersect	*in, t_material curr_material, t_light *l,  float *coef, t_menu *m);
t_color		ft_cast_ray1(t_scene	*s, t_intersect *in, t_menu *m);
t_color		ft_cast_ray2(t_scene	*s, t_intersect *in, t_menu *m);
t_color 	ft_path_trace(t_scene	*s, t_intersect *in, t_menu *m, int d);
t_vector	ft_vector_read(int fd);
t_color		ft_color_read(int fd);
t_material	ft_material_read(int fd);
void		ft_scene_read(t_scene *s, int fd);
t_object	*ft_sphere_read(int fd);
t_object	*ft_cylindre_read(int fd);
t_object	*ft_plane_read(int fd);
t_object	*ft_cone_read(int fd);

t_light		*ft_light_read(int fd);

t_vector	ft_point_at_parameter(t_ray *r, float t);
t_vector 	ft_normal_sphere(t_object *s, t_vector p);
t_vector 	ft_normal_plane(t_object *plane, t_vector p);
t_vector 	ft_normal_cone(t_object *cone, t_vector p);
t_vector 	ft_normal_cylindre(t_object *cylindre, t_vector p);
float		ft_intersection_sphere(t_object	*s, t_ray *r);
float		ft_intersection_plane(t_object	*p, t_ray *r);
float		ft_intersection_cone(t_object	*cone, t_ray *r);
float		ft_intersection_cylindre(t_object	*c, t_ray *r);

int			ft_sphere_compute(t_object *p, t_intersect *in, t_ray *r);
int			ft_plane_compute(t_object *p, t_intersect *in);
int			ft_cone_compute(t_object *p, t_intersect *in);
int			ft_cylindre_compute(t_object *p, t_intersect *in);

t_object	*ft_object_new(t_type type, t_object *o);
void		ft_object_push_back(t_object **lst, t_object *nw);
void		ft_object_push_front(t_object **lst, t_object *nw);
void		ft_object_pop_back(t_object **lst);
void		ft_object_clean(t_object **lst);
int			ft_object_length(t_object *lst);
t_object	*ft_object_get(t_object	*lst, int	id);
void		ft_object_set_id(t_object **lst);

t_light		*ft_light_new(t_vector pos, t_color color);
void		ft_light_push_back(t_light **lst, t_light *nw);
void		ft_light_push_front(t_light **lst, t_light *nw);
void		ft_light_pop_back(t_light **lst);
void		ft_light_clean(t_light **lst);
int			ft_light_length(t_light *lst);
#endif
