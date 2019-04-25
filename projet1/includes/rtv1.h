/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 20:04:01 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/25 17:10:57 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define SCR_WIDTH 1200
# define SCR_HEIGHT 750
# define W_W 900
# define W_H 450
# define B_W 960
# define B_H 600
# define START_X (SCR_WIDTH - B_W) / 2
# define START_Y (SCR_HEIGHT - B_H) / 2
# define END_X B_W + START_X
# define END_Y  B_H + START_Y
# define NB_THREADS 10
# define NB_OPTIONS 8
# define DELTA_ANGLE 10
# define ERR_CHECK(cond) if (!(cond)) perror(SDL_GetError());

# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"
# include "structs.h"

float		ft_rand48(void);
float		ft_clamp(float min, float max, float val);
t_vector		ft_reflect(t_vector i, t_vector n);
t_vector	  ft_refract1(t_vector i, t_vector n, float ior);
void		fresnel(t_vector i, t_vector n, float ior, float *kr);
void		ft_error(void);
int			ft_tab_len(char **tab);
void		ft_print_error(char *str);
void		ft_sdl_error(void);
t_font		ft_font(const char *message, const char *font_file, int font_size);

void		ft_sdl_quit(t_ptr *ptr);
void		ft_env_load_all(t_env *e);
void		ft_env_load_images(t_env *env);
void		ft_env_init(t_env *e, int argc, char *argv[]);
void		ft_env_update_camera(t_camera *c, t_menu m, float coef);
int			ft_process_event(t_env *e, t_input *in);
int			ft_update_options(t_menu *m, t_input *in, int k);
int			ft_mouse_inside(int mousex, int mousey, SDL_Rect *r);
void		ft_env_draw(t_env *e);
void		ft_draw(t_env *e);
void		ft_env_quit(t_env *e);

t_vector	ft_rotate_x(t_vector r, float angle);
t_vector	ft_rotate_y(t_vector r, float angle);
t_vector	ft_rotate_z(t_vector r, float angle);
t_vector	ft_rotate_vec3(t_vector r, t_vector v, int invert);
t_vector	ft_translate_vec3(t_vector r, t_vector v, int invert);

t_color		ft_get_light(t_intersect *in, t_light *light);
t_color		ft_trace(t_intersect *in, t_material m, t_light *l);
t_color		ft_ray_trace(t_scene *s, t_intersect *in, int depth);
t_color		ft_path_trace(t_scene *s, t_intersect *in, int depth);

t_vector	ft_vector_read(int fd);
t_color		ft_color_read(int fd);
t_material	ft_material_read(int fd);
t_object	*ft_sphere_read(int fd);
t_object	*ft_cylindre_read(int fd);
t_object	*ft_plane_read(int fd);
t_object	*ft_cone_read(int fd);
t_light		*ft_light_read(int fd);
void		ft_scene_init(t_scene *s, char *const input_file);
void		ft_scene_read(t_scene *s, int fd);
void		ft_parse_file(t_scene *s, int	fd);
void		ft_render(t_scene *s, Uint32 *pix);
void		ft_scene_clear(t_scene *s);

t_vector	ft_normal_sphere(t_object *s, t_vector p);
t_vector	ft_normal_plane(t_object *plane, t_vector p);
t_vector	ft_normal_cone(t_object *cone, t_vector p);
t_vector	ft_normal_cylindre(t_object *cylindre, t_vector p);

int			ft_sphere_compute(t_object *p, t_intersect *in);
int			ft_plane_compute(t_object *p, t_intersect *in);
int			ft_cone_compute(t_object *p, t_intersect *in);
int			ft_cylindre_compute(t_object *p, t_intersect *in);

int			ft_scene_intersect(t_scene *s, t_intersect *i);
int			ft_scene_intersectl(t_scene *s, t_intersect *i);
int			ft_sphere_intersect(t_object *s, t_ray *r, float *t);
int			ft_cone_intersect(t_object *s, t_ray *r, float *t);
int			ft_cylindre_intersect(t_object *plane, t_ray *r, float *t);
int			ft_plane_intersect(t_object *plane, t_ray *r, float *t);

t_object	*ft_object_new(t_type type, t_object *o);
void		ft_object_push_back(t_object **lst, t_object *nw);
void		ft_object_clean(t_object **lst);

t_light		*ft_light_new(t_vector pos, t_color color);
void		ft_light_push_back(t_light **lst, t_light *nw);
void		ft_light_clean(t_light **lst);

void		ft_update_event(t_input *in);
int			ft_sdl_init(t_ptr *ptr, const char *title);
int			ft_update_renderer(t_ptr *ptr, Uint32 *pixel);
SDL_Texture	*ft_get_render_text(SDL_Renderer *rend, t_font f, SDL_Color color);
void		ft_render_draw_img(SDL_Renderer *r, SDL_Texture *i, t_point p,\
		SDL_Rect *pos);
void		ft_sdl_error(void);
void		ft_clear_pixels(Uint32 *pixels);
#endif
